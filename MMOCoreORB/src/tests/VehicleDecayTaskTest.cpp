#include "gtest/gtest.h"

#include "conf/ConfigManager.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/creature/events/VehicleDecayTask.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {
namespace test {

class VehicleDecayTaskTest : public ::testing::Test {
public:
	VehicleDecayTaskTest() {
		ConfigManager::instance()->loadConfigData();
		ConfigManager::instance()->setProgressMonitors(false);
	}
};

TEST_F(VehicleDecayTaskTest, DefaultDecayRateIsReducedForInitialTick) {
	Reference<VehicleObject*> vehicle = new VehicleObject();
	Reference<VehicleObjectTemplate*> vehicleTemplate = new VehicleObjectTemplate();

	vehicle->_setObjectID(1);
	vehicle->initializeContainerObjectsMap();
	vehicle->setMaxCondition(100, false);
	vehicle->setConditionDamage(0, false);
	vehicle->loadTemplateData(vehicleTemplate);

	VehicleDecayTask decayTask(vehicle);
	decayTask.run();

	EXPECT_FLOAT_EQ(vehicle->getConditionDamage(), 2.f);
}

} // namespace test
} // namespace events
} // namespace creature
} // namespace objects
} // namespace zone
} // namespace server
