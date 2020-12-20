#include <api\Loader.h>
#include <mcapi/BlockSource.h>
#include <mcapi/Block.h>
#include <string>


using namespace std;
namespace updata {
	inline  Player* updateInventory() {
		return SymCall("?forceBalanceTransaction@InventoryTransactionManager@@QEAAXXZ", void) ;
	}
}