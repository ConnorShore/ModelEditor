EXE=app

# Main target
all: $(EXE)

#Windows
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lglu32 -lopengl32 -lSDL2main -lSDL2
CLEAN=del *.exe *.o *.a
else
#Linux
CFLG= -O3 -Wall -o $(EXE)
LIBS=-lSDL2 -lGLEW -lGL -lm
CLEAN=rm -f $(EXE) *.o *.a
endif

FILES=main.cpp MainEditor.h MainEditor.cpp ShaderProgram.h ShaderProgram.cpp StaticShader.h StaticShader.cpp Math.h Camera.h Camera.cpp GameObject.h Primitive.h Primitive.cpp Cube.h Cube.cpp Vertex.h Renderer.h Renderer.cpp InputManager.h InputManager.cpp Timing.h Timing.cpp Light.h Light.cpp PointLight.h PointLight.cpp DirectionalLight.h DirectionalLight.cpp Picker.h Picker.cpp Physics.h Physics.cpp OutlineShader.h OutlineShader.cpp TransformController.h TransformController.cpp TransformShader.h TransformShader.cpp GUI.h GUI.cpp GUIShader.h GUIShader.cpp


# Link
app:
	g++ $(CFLG) $(FILES) $(LIBS)

run:
	./$(EXE)

clean:
	$(CLEAN)