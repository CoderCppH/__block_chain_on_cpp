#pragma once
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include <openssl/evp.h>
namespace __args_bch {

}
namespace __node_block_chain {
	struct _Block{
		std::string _prevHash;
		std::string _hash;
		std::string _data;
		time_t _ttmap;
		_Block(std::string data, std::string prevHash) {
			this->_data = data;
			this->_prevHash = prevHash;
			this->_ttmap = time(0);
			this->_hash = _gen_hash();
		}
	private:
		std::string _gen_hash() {
			std::stringstream ss;
			ss << _prevHash << _ttmap << _data;
			return _sha256(ss.str());
		}
		std::string _sha256(const std::string sol) {
			unsigned char hash[32];
			EVP_MD_CTX* ctx = EVP_MD_CTX_new();
			EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
			EVP_DigestUpdate(ctx, sol.c_str(), sol.size());
			EVP_DigestFinal_ex(ctx, hash, NULL);
			EVP_MD_CTX_free(ctx);
			std::stringstream ss;
			for (int i = 0; i < 32; i++) 
				ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
			return ss.str();
		}
	};
}
namespace __block_chain {
	struct _BLockChain {
	private:
		std::vector<__node_block_chain::_Block> _vec_chain;
	public:
		_BLockChain() {
			_vec_chain.emplace_back("__main_start_ref_block_chain", "0");
		}
		void addBlock(std::string data) {
			__node_block_chain::_Block _n_block(data, _vec_chain.back()._hash);
			_vec_chain.push_back(_n_block);
		}
		void printChain() {
			for (const auto& _i_block : _vec_chain) {
				std::cout << "Block:\n";
				std::cout << "Previous Hash: " << _i_block._prevHash << "\n";
				std::cout << "Data: " << _i_block._data << "\n";
				std::cout << "Hash: " << _i_block._hash << "\n";
				std::cout << "Timestamp: " << _i_block._ttmap << "\n";
				std::cout << "------------------------\n";
			}
		}
	};
}