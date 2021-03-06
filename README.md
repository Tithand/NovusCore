# NovusCore

### What is NovusCore

NovusCore is an emulating project for World of Warcraft. We aim to support as many versions as we can, in an as flexible manner as possible, meaning that the aim to make it 'easier' to have multiple game builds supported by the same core.

Currently NovusCore is being written baseline for the Wrath of the Lich King 3.3.5a 12340 client build. This is to better enable us to design our architecture around the WoW Client. 


### The NovusCore Promise

The project was made with the promise that we would always focus on reliability, redundancy, and performance over convenience. We achieve this through making use of experience, but also applying modern techniques and design patterns.

The end-goal is to provide a core capable of tackling all of the current limitations set by the cores available. Solving those issues are complicated, but we start by applying a proper foundation for our architecture to allow for better flow of information(data) and performance.


### NovusCore Discord

The project has an official [Discord](https://discord.gg/gz6FMZa).
You will find the developers to be active on the discord and always up for answering any questions you might have regarding the project. Despite NovusCore not currently being ready for production level use, we are always welcoming any users that want to try using it.


### Dependencies
* [Asio](http://sourceforge.net/projects/asio/files/asio/1.12.1%20%28Stable%29/)
* [OpenSSL 1.0.2q](http://slproweb.com/products/Win32OpenSSL.html)
* [MySQL C Connector 5.6 (libmysqlcclient) or newer](https://dev.mysql.com/downloads/connector/c/)
* [CMAKE 3.1 or newer](https://cmake.org/download/)


### Libraries
Here we include a honorable mention to all the libraries included directly into the source of NovusCore. You do not need to download these on your own, but we felt it was important to address these as without them, NovusCore would be a lot more time consuming to develop.
* [Fast MPMC Queue](https://github.com/spectre1989/fast_mpmc_queue)
* [Nlohmann Json](https://github.com/nlohmann/json/)
* [Amy](https://github.com/liancheng/amy)
* [Tracy Profiler](https://bitbucket.org/wolfpld/tracy/src/master/)
* [Entt ECS](https://github.com/skypjack/entt)
* [Cpp-Taskflow](https://github.com/cpp-taskflow/cpp-taskflow)
* [ZLIB](https://github.com/madler/zlib)
