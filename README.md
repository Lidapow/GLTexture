# GLTexture

## FFMPEG CLI commands
./ffmpeg -r 30 -s 640x480 -f avfoundation -i "0" -f rawvideo -b 64k -r 60 -s 640x480 -an tcp://localhost:8080

./ffmpeg -r 30 -s 640x480 -f avfoundation -i "0" -f rawvideo -pix_fmt rgb24 -b 64k -r 60 -s 640x480 -an tcp://localhost:8080

./ffmpeg -r 60 -s 640x480 -f avfoundation -i "2" -f rawvideo -pix_fmt rgb24 -b 64k -r 60 -s 640x480 -an udp://localhost:8080