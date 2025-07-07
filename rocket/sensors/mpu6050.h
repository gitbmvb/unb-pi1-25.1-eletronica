#pragma once
struct MPUData { float ax, ay, az, gx, gy, gz, temp; };
bool initMPU();
bool readMPU(MPUData &d);
