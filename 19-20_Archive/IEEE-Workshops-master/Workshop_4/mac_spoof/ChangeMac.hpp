#ifndef CHANGE_MAC_HPP
#define CHANGE_MAC_HPP

#include <cstdint>
#include <string>

void makeRandomMac(uint8_t mac[6]);

bool setRandomMac(uint8_t mac[6]);

bool changeMac(const uint8_t mac[6]);

#endif // CHANGE_MAC_HPP
