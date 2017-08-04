function initialize(level)
    maxenemies = get_startenemycount(level);

    for i=0, maxenemies, 1 do
        spawn(level, "basic_enemy.lua")
    end
end

function spawn_enemy(level)
    spawn(level, "basic_enemy.lua", 0)
end		
