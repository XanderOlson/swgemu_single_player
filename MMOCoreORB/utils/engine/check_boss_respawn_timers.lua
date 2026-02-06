#!/usr/bin/env lua

local root = debug.getinfo(1, "S").source:sub(2):match("^(.*)/utils/engine/")
if not root then
  io.stderr:write("Unable to determine repo root.\n")
  os.exit(1)
end

local checks = {
  ["bin/scripts/screenplays/poi/tatooine_ancient_krayt_dragon_skeleton.lua"] = {
    "krayt_dragon_grand",
    "krayt_dragon_ancient",
    "giant_canyon_krayt_dragon",
    "canyon_krayt_dragon",
    "juvenile_canyon_krayt_dragon",
    "krayt_dragon_adolescent",
  },
  ["bin/scripts/screenplays/poi/tatooine_krayt_graveyard.lua"] = {
    "canyon_krayt_dragon",
    "juvenile_canyon_krayt_dragon",
    "giant_canyon_krayt_dragon",
    "krayt_dragon_grand",
    "krayt_dragon_ancient",
    "krayt_dragon_adolescent",
  },
  ["bin/scripts/screenplays/poi/tatooine_village_ruins.lua"] = {
    "krayt_dragon_adolescent",
  },
  ["bin/scripts/screenplays/static_spawns/tatooine_static_spawns_south.lua"] = {
    "krayt_dragon_adolescent",
    "krayt_dragon_grand",
  },
  ["bin/scripts/screenplays/poi/dathomir_nightsister_labor_camp.lua"] = {
    "nightsister_elder",
  },
  ["bin/scripts/screenplays/poi/dathomir_nightsister_vs_singing_mountain.lua"] = {
    "nightsister_elder",
  },
  ["bin/scripts/screenplays/poi/dathomir_nightsister_stronghold.lua"] = {
    "nightsister_elder",
  },
  ["bin/scripts/screenplays/caves/dathomir_spider_clan_cave.lua"] = {
    "spiderclan_elder",
  },
  ["bin/scripts/screenplays/static_spawns/dathomir_static_spawns_sw.lua"] = {
    "nightsister_elder",
  },
  ["bin/scripts/screenplays/static_spawns/dathomir_static_spawns_se.lua"] = {
    "spiderclan_elder",
    "nightsister_elder",
  },
  ["bin/scripts/screenplays/static_spawns/dathomir_static_spawns_nw.lua"] = {
    "nightsister_elder",
  },
}

local respawn_event_file = "bin/scripts/screenplays/poi/dathomir_nightsister_stronghold.lua"
local respawn_event_pattern = "createEvent%(%s*180%s*%*%s*1000"

local function read_file(path)
  local file = io.open(path, "r")
  if not file then
    return nil
  end
  local content = file:read("*a")
  file:close()
  return content
end

local function assert_spawn_timer(path, npc)
  local content = read_file(path)
  if not content then
    return {string.format("missing file: %s", path)}
  end
  local pattern = string.format("spawnMobile%%([^)]-\\\"%s\\\"%%s*,%%s*180", npc)
  if not content:find(pattern) then
    return {string.format("%s: missing 180s spawnMobile for %s", path, npc)}
  end
  return {}
end

local function main()
  local errors = {}

  for rel_path, npcs in pairs(checks) do
    for _, npc in ipairs(npcs) do
      local results = assert_spawn_timer(root .. "/" .. rel_path, npc)
      for _, err in ipairs(results) do
        table.insert(errors, err)
      end
    end
  end

  local respawn_content = read_file(root .. "/" .. respawn_event_file)
  if not respawn_content then
    table.insert(errors, string.format("missing file: %s", respawn_event_file))
  elseif not respawn_content:find(respawn_event_pattern) then
    table.insert(errors, string.format("%s: missing 180s createEvent respawn", respawn_event_file))
  end

  if #errors > 0 then
    io.write("Respawn timer checks failed:\n")
    for _, err in ipairs(errors) do
      io.write("- " .. err .. "\n")
    end
    return 1
  end

  io.write("Respawn timer checks passed.\n")
  return 0
end

os.exit(main())
