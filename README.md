# SonicRobot
Multi sensor install on the 'official' arduino robot.

Starting with tom Igoe's original code http://arduino.cc/en/Tutorial/ping with code provided by daniel-boersen@hotmail.com who got it working for one sensor I got it working with 3 sensors, and then got the code cleaned up with the help of Andre Bellucci (http://dei.inf.uc3m.es/abellucci/), I now have a fully functioning 3 sensor array using the HC-SR04 sensor. The code adds to the general "go forward until you sense something x CM away, then turn right". When the front sensor is triggered, the other two sensors are checked and the robot will go in the direction that has the longest/farthest ping. If both left and right are identical, then the robot turns around and goes back in the direction it came.

None of this can be understood in terms of the official arduino robot (http://arduino.cc/en/Main/Robot) without recourse to Fabio Ciravegna's blog (http://fabcirablog.weebly.com/blog/archives/12-2013) which explains the crazy pins.

I'll update with photos when things are more stable and I solder the parts on.

I'll be adding a 4th sonic sensor, and a capacitive sensor to watch for actually hitting things.

I'll be adding a mozzi synth function as well.

