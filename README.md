# NL LIB
The 5th iteration of my own game development framework. (Yes, I have done this 5 times!)


![Programmer Art Logo](https://raw.githubusercontent.com/NickTheSic/nlGameFramework/refs/heads/main/res/icon0.png)
 
## About
It is easy to use game engines like Unreal and premade frameworks like Raylib or SDL.  But there is something special about working low level and creating from the operating system. I have ported games to the Nintendo Switch, but they were Unreal Engine projects and the engine code was already there for me.  And while SDL has their own repo, software like raylib and godot don't have a premade implementation.  How do you roll your own platform layer if you don't have experience?

## Use
Very incomplete and constantly being update.  No standardized ABI yet as lots will change. I know how I would like the end use to be but getting there is the challenge.  I would suggest raylib or SDL, or checkout Handmade Hero to learn more and make games.  This is very much for my own use and learning.

## Attempt 5
Yes, I have used GLFW and GLAD along with C++ to try and make this before.  Each time it gets to a state where I can make a game I realize I don't like using what I just created.  Everytime before I started from scratch, but this time I went with bare C and set things up. I see where I want to add C++ features like operator overloading or function overloading, (And a nicer String implementation than C) and I can add it in slowly as I change files.  Iteration is important and starting from scratch each time is good for C++ but I liked the c data framework I was making and this is an implementation like that.  Raylib and SDL are what the end goal is, but less abstraction and more specific game code in the end

