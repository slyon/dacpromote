#include <dacpromote.hpp>

// Add dummy action to satisfy the compiler:
// https://github.com/EOSIO/eosio.cdt/issues/468
void dacpromote::dummy() {
  return;
}

// Get notified about new accounts via the "cointreasury" contract
// from our "EOS Gift Card" partner app
void dacpromote::on_eosgiftcard( name new_account ) {
  name partner = name("cointreasury");
  require_auth(partner);

  check( is_account( new_account ), "new_account does not exist");
  accounts accountstable( TOK, get_self().value );
  const auto& ac = accountstable.find( CODE.raw() );

  asset t;
  if(ac != accountstable.end()) {
    t = ac->balance;
  } else {
    t = asset(0, SYM);
  }

  const int amnt = 50; //50
  if (t.amount >= amnt) {
    // transfer 50 MAIL tokens, if 50 or more left
    const std::string memo = string("Visit dmail.co");
    action(
      permission_level{ get_self(), "active"_n },
      TOK, "transfer"_n,
      make_tuple(get_self(), new_account, asset(amnt, SYM), memo)
    ).send();
  }

  return;
}

