/**
 * @file domain_resolver.cc
 * @brief Map IPs to domains and domains to subdomains with fast lookups
 *
 * This file implements a DomainResolver class for a shared hosting server
 * where multiple domains can live on the same IP and each domain can have
 * multiple subdomains. Two hash maps of hash sets provide O(1) average-time
 * registration and membership queries.
 *
 * Key Concepts:
 * - Nested hashing: unordered_map<string, unordered_set<string>>
 * - One map for IP -> domains, another for domain -> subdomains
 * - has_subdomain validates the full IP -> domain -> subdomain chain
 *
 * Time Complexity:
 *   - register_domain / register_subdomain: O(1) average
 *   - has_subdomain: O(1) average
 *
 * Space Complexity: O(D + S)
 *   - D total domain registrations, S total subdomain registrations
 */

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/**
 * @brief Resolver tracking IP->domain and domain->subdomain associations
 */
class DomainResolver {
  private:
  unordered_map<string,unordered_set<string>> ip_to_domain; // {ip: {domains}};
  unordered_map<string,unordered_set<string>> domain_to_subdomain; // {domain: {subdomain}};
  public:
  DomainResolver();
  ~DomainResolver();
  void register_domain(const string& ip, const string& domain);
  void register_subdomain(const string& domain, const string& subdomain);
  bool has_subdomain(const string& ip, const string& domain,const string& subdomain);
};

/** @brief Construct an empty resolver with no registered associations */
DomainResolver::DomainResolver() {
  ip_to_domain = {};
  domain_to_subdomain = {};
}

DomainResolver::~DomainResolver() {}

/**
 * @brief Associate a domain with an IP address
 *
 * @param ip     The IP address hosting the domain
 * @param domain The domain name to register under that IP
 */
void DomainResolver::register_domain(const string &ip, const string &domain) {
  ip_to_domain[ip].insert(domain);
}

/**
 * @brief Add a subdomain to a previously registered domain
 *
 * @param domain    The parent domain (assumed already registered)
 * @param subdomain The subdomain to attach to the domain
 */
void DomainResolver::register_subdomain(const string &domain, const string &subdomain) {
  domain_to_subdomain[domain].insert(subdomain);
}

/**
 * @brief Check whether a subdomain exists under a domain hosted on an IP
 *
 * @param ip        The IP address to query
 * @param domain    The domain expected at that IP
 * @param subdomain The subdomain expected under that domain
 * @return true only if every link of the IP -> domain -> subdomain chain holds
 *
 * The query passes only when all four conditions are true:
 * 1. The IP is registered.
 * 2. That IP hosts the given domain.
 * 3. The domain has subdomains registered.
 * 4. The given subdomain is one of them.
 */
bool DomainResolver::has_subdomain(const string &ip, const string &domain, const string &subdomain) {
   return (ip_to_domain.find(ip) != ip_to_domain.end()) /*ip present*/ &&
          (ip_to_domain[ip].find(domain) != ip_to_domain[ip].end()) /*ip has this domain*/ && 
          (domain_to_subdomain.find(domain) != domain_to_subdomain.end()) /*domain is present*/ &&
          (domain_to_subdomain[domain].find(subdomain) != domain_to_subdomain[domain].end()); /* domain has subdomain or not*/
}


/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Example 1: register domains/subdomains, then query various chains
  DomainResolver resolver = DomainResolver();
  resolver.register_domain("192.168.1.1", "example.com");
  resolver.register_domain("192.168.1.1", "example.org");
  resolver.register_domain("192.168.1.2", "domain.com");
  resolver.register_subdomain("example.com", "a");
  resolver.register_subdomain("example.com", "b");
  cout<<boolalpha;
  cout<<resolver.has_subdomain("192.168.1.1", "example.com", "a")<<"\n";    // Returns True
  cout<<resolver.has_subdomain("192.168.1.1", "example.com", "c")<<"\n";    // Returns False (subdomain "c" not registered)
  cout<<resolver.has_subdomain("127.0.0.1", "example.com", "a")<<"\n";      // Returns False (IP not registered)
  cout<<resolver.has_subdomain("192.168.1.1", "example.org", "a")<<"\n";    // Returns False (example.org has no subdomains)
  cout<<resolver.has_subdomain("192.168.1.2", "example.com", "a")<<"\n";    // Returns False (example.com not on this IP)
  cout<<"---------------------\n";

  // Example 2: single domain + subdomain, matching query
  DomainResolver resolver1 = DomainResolver();
  resolver1.register_domain("1.1.1.1", "test.com");
  resolver1.register_subdomain("test.com", "www");
  cout<<resolver1.has_subdomain("1.1.1.1", "test.com", "www")<<"\n";        // Returns True
  cout<<"---------------------\n";

  // Example 3: empty resolver -> every query is False
  DomainResolver resolver2 = DomainResolver();
  cout<<resolver2.has_subdomain("1.1.1.1", "test.com", "www")<<"\n";        // Returns False
  cout<<"---------------------\n";

  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Domain Resolver
 *
 * You manage a shared web hosting server with multiple IP addresses, and where
 * multiple domains can share the same IP address. Each domain can have multiple
 * subdomains.
 *
 * Implement a class, `DomainResolver`, that supports three methods:
 *
 * - `register_domain(ip, domain)`: associates a domain with an IP. You can
 *   assume that this function will be called at most once for a given domain.
 * - `register_subdomain(domain, subdomain)`: adds a subdomain to a domain. You
 *   can assume that the domain will have been previously registered. Different
 *   domains can have a subdomain with the same name.
 * - `has_subdomain(ip, domain, subdomain)`: returns whether there is a domain
 *   registered at that IP that has the given subdomain.
 *
 * `IPs`, `domains`, and `subdomains` are strings.
 *
 * Example 1:
 * resolver = DomainResolver()
 * resolver.register_domain("192.168.1.1", "example.com")
 * resolver.register_domain("192.168.1.1", "example.org")
 * resolver.register_domain("192.168.1.2", "domain.com")
 * resolver.register_subdomain("example.com", "a")
 * resolver.register_subdomain("example.com", "b")
 * resolver.has_subdomain("192.168.1.1", "example.com", "a")  # Returns True
 * resolver.has_subdomain("192.168.1.1", "example.com", "c")  # Returns False
 * resolver.has_subdomain("127.0.0.1", "example.com", "a")    # Returns False
 * resolver.has_subdomain("192.168.1.1", "example.org", "a")  # Returns False
 * resolver.has_subdomain("192.168.1.2", "example.com", "a")  # Returns False
 *
 * Example 2:
 * resolver = DomainResolver()
 * resolver.register_domain("1.1.1.1", "test.com")
 * resolver.register_subdomain("test.com", "www")
 * resolver.has_subdomain("1.1.1.1", "test.com", "www")  # Returns True
 *
 * Example 3:
 * resolver = DomainResolver()
 * resolver.has_subdomain("1.1.1.1", "test.com", "www")  # Returns False
 *
 * Constraints:
 * - The number of calls to `register_domain` and `register_subdomain` will be
 *   at most `10^5`
 * - The number of calls to `has_subdomain` will be at most `10^5`
 * - All `IPs` follow the IPv4 format
 * - Each octet is a number between `0` and `255`
 * - All domains and subdomains are non-empty strings of length at most `100`
 *
 *============================================================================*/
