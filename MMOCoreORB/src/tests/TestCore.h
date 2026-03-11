/*
 * TestCore.h
 *
 *  Created on: 03/09/2013
 *      Author: victor
 */

#ifndef TESTCORE_H_
#define TESTCORE_H_

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <vector>

#include "engine/engine.h"

#include "server/db/MySqlDatabase.h"

class TestCore : public Core, public Logger {
public:
	TestCore() : Core(0), Logger("TestCore") {
		configureLuaRuntime();
	}

	~TestCore() {
		finalizeContext();
	}

	void initialize() override {
		 server::db::mysql::MySqlDatabase::initializeLibrary();
	}

	void run() override {

	}

	void finalizeContext() override {
		server::db::mysql::MySqlDatabase::finalizeLibrary();
	}

	bool runLuaSmokeTest() const {
		if (!luaPathsConfigured) {
			error("Lua paths were not configured; cannot validate script availability.");
			return false;
		}

		const std::vector<std::filesystem::path> requiredScripts = {
			luaScriptsRoot / "object" / "main.lua",
			luaScriptsRoot / "loot" / "loot_manager.lua",
			luaScriptsRoot / "managers" / "mission" / "mission_npc_spawn_points.lua"
		};

		bool allFound = true;

		for (const auto& scriptPath : requiredScripts) {
			if (!std::filesystem::exists(scriptPath)) {
				error() << "Missing Lua script: " << scriptPath.string();
				allFound = false;
			}
		}

		if (allFound) {
			info(true) << "Lua smoke test succeeded (required scripts found).";
		}

		return allFound;
	}

private:
	std::filesystem::path luaScriptsRoot;
	std::filesystem::path luaBinRoot;
	bool luaPathsConfigured = false;

	void configureLuaRuntime() {
		namespace fs = std::filesystem;

		fs::path probe = fs::current_path();
		for (int depth = 0; depth < 8; ++depth) {
			fs::path candidate = probe / "MMOCoreORB" / "bin" / "scripts";
			if (fs::exists(candidate)) {
				luaScriptsRoot = candidate;
				luaBinRoot = candidate.parent_path();
				break;
			}

			if (!probe.has_parent_path()) {
				break;
			}

			probe = probe.parent_path();
		}

		if (luaScriptsRoot.empty()) {
			error("Unable to locate MMOCoreORB/bin/scripts; Lua paths not configured.");
			return;
		}

		try {
			fs::current_path(luaBinRoot);
		} catch (const std::exception& ex) {
			error() << "Failed to set working directory to " << luaBinRoot.string() << ": " << ex.what();
			return;
		}

		std::string luaPath = (luaScriptsRoot / "?.lua").string();
		luaPath += ";";
		luaPath += (luaScriptsRoot / "?" / "init.lua").string();

		if (const char* existing = std::getenv("LUA_PATH")) {
			if (std::strlen(existing) > 0) {
				luaPath += ";";
				luaPath += existing;
			}
		}

		setenv("LUA_PATH", luaPath.c_str(), 1);
		luaPathsConfigured = true;
		info() << "Lua runtime configured. Working directory set to " << luaBinRoot.string()
		       << " with LUA_PATH=" << luaPath;
	}
};


#endif /* TESTCORE_H_ */
