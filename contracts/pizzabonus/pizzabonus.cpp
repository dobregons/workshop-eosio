#include <eosio/eosio.hpp>
#include "./pizzabonus.h"

pizzabonus::pizzabonus(name self_contract, name user, eosio::datastream<const char*> ds) 
: contract(self_contract, user, ds), ut(""_n, ""_n.value) {
  coupon_threshold = 5;
}

void pizzabonus::buypizza(name user) {
  //
}

uint16_t pizzabonus::getcoupons(name user) {
  //
  return 0;
}

void pizzabonus::redeemcoupon(name user) {
  //
}

void pizzabonus::chngthrhld(name user, uint16_t newvalue) { 
  //
}
