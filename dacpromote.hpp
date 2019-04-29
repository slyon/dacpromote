#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

using namespace std;
using namespace eosio;

const string _sym = "EOSDAC";
const name TOK = name("eosdactokens");
const symbol_code CODE = symbol_code(_sym);
const symbol SYM = symbol(_sym, 4);

CONTRACT dacpromote : public eosio::contract {
  public:
    using contract::contract;

    TABLE account {
        asset balance;
        uint64_t primary_key() const { return balance.symbol.code().raw(); }
    };
    typedef eosio::multi_index<"accounts"_n, account> accounts;

    ACTION dummy();

    [[eosio::on_notify("cointreasury::notify")]]
    void on_eosgiftcard( name new_account );

    dacpromote( name receiver, name code, datastream<const char*> ds ):
      contract( receiver, code, ds ) {}
};
