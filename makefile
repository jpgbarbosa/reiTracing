all:
	g++ main.cpp Ray.cpp Sphere.cpp Light.cpp -o rayTracer.exe -lm -lglu32 -lglut32 -lopengl32