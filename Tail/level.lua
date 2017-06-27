function initialize(level)
    maxenemies = get_maxenemies(level);

    for i=0, maxenemies, 1 do
        spawn(level, "follower.lua")
    end
end

function spawn_enemy(level)
    spawn(level, "follower.lua", 0)
end		
