-- TODO: Make a simplem test file for testing lua embedding

print('Simple Lua Script Executing!')
print('Getting an execute line by line')
print('for the purpose of a visual novel')

print('Loading Sound')
laser_sfx = load_sound('laserHit.wav')
print('Will play sound')
play_sound(laser_sfx)
