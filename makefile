roadImages: roadImages.cpp
	g++ roadImages.cpp -o roadImages `/usr/local/Cellar/pkg-config/0.28/bin/pkg-config opencv` `/usr/local/Cellar/pkg-config/0.28/bin/pkg-config --libs opencv`

#testHoughCircles: testHoughCircles.cpp
#	g++ testHoughCircles.cpp -o testHoughCircles `/usr/local/Cellar/pkg-config/0.28/bin/pkg-config opencv` `/usr/local/Cellar/pkg-config/0.28/bin/pkg-config --libs opencv`

