#include "./pizzabonus.h"

pizzabonus::pizzabonus(name self_contract, name receiver, eosio::datastream<const char*> ds) 
: contract(self_contract, receiver, ds), ut(""_n, ""_n.value) {
  eosio::print("name 1: ", self_contract, "   name 2: ", receiver);

  // @TODO: research passing custom parameters to the contract constructor
  // @TODO: cases for threshold as 1
  coupon_threshold = 5;
}

void pizzabonus::buypizza(name user) {
  // user exist?
  eosio::require_auth(user);

  auto iterator = ut.find(user.value);
  if (iterator == ut.end()) {
    eosio::print("register new user: ", user);

    ut.emplace(user, [&](auto& row) {
      row.username = user;
      row.coupons = 0;
      row.pizzasbought = 1;
    });
  } else {
    ut.modify(iterator, user, [&](auto& row) {
      row.pizzasbought++;
      eosio::print(user, " bought a pizza, counter: ", row.pizzasbought);

      if(row.pizzasbought == coupon_threshold) {
        row.coupons++;
        row.pizzasbought = 0;

        eosio::print(user, " wins a coupon, coupons: ", row.coupons);
      }
    });

  }
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
