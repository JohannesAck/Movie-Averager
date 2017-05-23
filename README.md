# Movie-Averager
QT Program that averages the color of each Frame of an input Video and produces an image representing the averages of 
each frame as a single pixel column, which is then scaled, since I don't own a 100k monitor

# Usage
Requires opencv as a dynamic link library, adjust path in launch.sh or .pro file accordingly. 
Compile with qmake or from qt creator.
Afterwards the GUI should be self explanatory.
However, currently the program is quite slow for long or high resolution videos

# Further Improvments:
 * Generally speed up
 * Fix error output from file dialogue
 * Keep GUI from freezing while processing video.
 * Statically compile OpenCV to remove dependence on link library.
 
# Notes:
 * Inspired by [this reddit thread](https://www.reddit.com/r/dataisbeautiful/comments/3rb8zi/the_average_color_of_every_frame_of_a_given_movie/), whose creator didn't want to make his code publicly available.
 * 
