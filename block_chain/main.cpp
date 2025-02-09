#include<iostream>
#include "source/block_shain.h"
int main(int argc, char* argv[]) {
	__block_chain::_BLockChain _block;
	_block.addBlock("My password");
	_block.addBlock("Your password");
	_block.addBlock("These password");

	_block.printChain();
	return EXIT_SUCCESS;
}