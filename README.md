### Steps to build and run:
1. Compile program:
```
gcc -g *.cpp -o napatech_stat \
  -std=c++11 \
  -Iinclude \
  -Llib \
  -lntapi \
  -lntos \
  -lstdc++ \
  -lprometheus-cpp-core \
  -lprometheus-cpp-pull
```
2. Create file `/etc/ld.so.conf.d/napatech.conf` and insert there full path of the project's `lib` directory (example: `/home/user/napatech-stat/lib`)
3. Run `sudo ldconfig`
4. To start capturing metrics for 2 ports (0-1) and 32 streams (0-31), run `./napatech_stat 77.77.77.77:8080 2 32`
5. Add new config section on the Prometheus' instance side and specify new target for scraping:
```
scrape_configs:
  - job_name: 'napatech_stat'
    static_configs:
    - targets: ['77.77.77.77:8080']
```