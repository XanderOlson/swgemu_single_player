/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef VEHICLEDECAYTASK_H_
#define VEHICLEDECAYTASK_H_

#include "server/zone/objects/tangible/TangibleObject.h"
#include "templates/creature/VehicleObjectTemplate.h"

class VehicleDecayTask : public Task, public Logger {
	ManagedWeakReference<TangibleObject*> vehicleObj;
	bool initialDecay;

	int getInitialDecayAmount(int decayRate) const {
		// Initial decay tick is reduced, but always applies at least 1 point of damage.
		int initialAmount = decayRate / 2;
		return initialAmount > 0 ? initialAmount : 1;
	}

public:
	VehicleDecayTask(TangibleObject* veh) : Task() {
		vehicleObj = veh;
		initialDecay = true;
		setLoggingName("VehicleDecayTask");
	}

	void run() {
		ManagedReference<TangibleObject*> vehicle = vehicleObj.get();

		if (vehicle == nullptr)
			return;

		Reference<VehicleObjectTemplate*> vehicleTemplate = cast<VehicleObjectTemplate*>(vehicle->getObjectTemplate());

		if (vehicleTemplate == nullptr)
			return;

		Locker locker(vehicle);

		vehicle->removePendingTask("decay");

		int decayCycle = vehicleTemplate->getDecayCycle();

		if (decayCycle == 0)
			decayCycle = 600;

		int decayRate = vehicleTemplate->getDecayRate();

		if (decayRate == 0)
			decayRate = 5;

		if (initialDecay) {
			int initialAmount = getInitialDecayAmount(decayRate);
			info() << "Initial vehicle decay tick: decayRate=" << decayRate
			       << " initialAmount=" << initialAmount
			       << " vehicleId=" << vehicle->getObjectID();
			vehicle->inflictDamage(vehicle, 0, initialAmount, true);
			initialDecay = false;
		} else {
			vehicle->inflictDamage(vehicle, 0, decayRate, true);
		}

		vehicle->addPendingTask("decay", this, decayCycle * 1000);
	}
};

#endif /*VEHICLEDECAYTASK_H_*/
