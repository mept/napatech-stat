### Steps to build:
1. Create file `/etc/ld.so.conf.d/napatech.conf` and insert there full path of the project's `lib` directory (example: `/home/user/napatech-stat/lib`)
2. Run `sudo ldconfig`
3. Execute `/usr/bin/gcc -fdiagnostics-color=always -g main.cpp -o napatech_stat -Llib -lntapi -lntos -L/usr/lib64 -lstdc++ -L /usr/lib/ -lpthread -std=c++11`
4. `./napatech_stat`
