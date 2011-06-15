all:
	g++ main.cpp Cube.cpp Object.cpp Plane.cpp PlaneChess.cpp Ray.cpp Sphere.cpp Light.cpp rayTracer.cpp scene.cpp -o rayTracer.exe -lm -lglu32 -lglut32 -lopengl32 -lpthread -D_REENTRANT -g