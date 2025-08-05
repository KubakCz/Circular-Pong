# Devlog

### Math

#### Vector

- 18.09.2022 (1.5 h)
  -  Framework exploration
  -  Fighting with templates
- 22.09.2022 (1 h)
  - Working on vector math
- 23.09.2022 (3 h) 
  - Trying to make loop unwraping working
  - Nearly finishing Vector\<N\> class
- 29.09.2022 (0.75 h)
  - Aplying feedback
- 03.10.2022 (0.75 h)
  - Better constructors and element access for vec2, vec3, and vec4
  - Finishing Vector

#### Polar coordinates

- 27.09.2022 (1.5 h)
  - Done
- 06.10.2022 (0 h)
  - Add getters

#### Matrix

- 26.09.2022 (2 h)
  - Basic matrix math
- 03.10.2022 (1 h)
  - Matrix from and to basis vectors
  - Small modifications to code
- 08.10.2022 (few minutes)
  - Multiplication and division by scalar

#### Quaternion

- 06.10.2022 (2 h)
  - Quaternion math and tests
- 07.10.2022 (1 h)
  - Testing and debuging
- 08.10.2022 (3.5 h)
  - Quaternion conversions
  - Axis-Angle -- Note: I find it pointless to implement separate class for axis angle, if the only thing it can do is to convert itself to a quaternion
- 13.10.2022 (0 h)
  - repair slerp

### Camera and basic rendering
- 09.10.2022 (1 h)
  - Creating transform component
  - Starting work on camera class
- 12.10.2022 (2 h)
  - Projection things
  - Trying to make camera work with project
- 13.10.2022 (1 h)
  - Mostly thinking
- 18.10.2022 (1 h)
  - Trying to import glad.h
- 19.10.2022 (4.25 h)
  - Basic unlit shader
  - Uniform structs for the shader
  - Model matrix computation
  - Class for holding geometry data
  - Vector constants
- 20.10.2022 (4 h)
  - Bugfixes
- 21.10.2022 (1 h)
  - Bugfixes
- 25.10.2022 (2.25 h)
  - Projections finally works
  - Line rendering finally works

### Adding useful things and cleanup
- 27.10.2022 (1 h)
  - Resource meneger not working
- 28.10.2022 (4 h)
  - Basic resource manager
  - Vector casting
  - Input system
- 29.10.2022 (1 h)
  - Mat->Quat conversion

### Geometry generation
- 29.10.2022 (2.5 h)
  - Shader for displaying normals
  - A bit of code to check face orientation
  - Circle generation
  - Cube generation
- 31.10.2022 (2 h)
  - Sphere generation
- 1.11.2022 (1,75 h)
  - Brick / paddle generation

### Lights
- 1.11.2022 (2 h)
  - Light UBO
  - Shader manager
- 3.11.2022 (1 h)
  - Phong model and textures

### Adding useful things and cleanup 2
- 4.11.2022 (2 h)
  - Change inner representation of matrix to match opengl
  - Debug cross
  - Make Vec and Transform constants static memebers
  - Replace ResourceManager with TextureManager 
- 6.11.2022 (2,5 h)
  - Multiple lights buffer

### Game stuff
- 9.11.2022 (4,25 h)
  - Base for game objects
  - Environment properties
  - Storage classes for materials and geometries
- 10.11.2022 (2,5 h)
  - Basic game objects
- 12.11.2022 (2 h)
  - Switchable camera
- 15.11.2022 (5 h)
  - Paddle controller and paddle motion
  - Axis angle representation
  - Brick manager and brick spawning

### Graphics
- 16.11.2022 (3 h)
  - Working on ball occlusion
- 17.11.2022 (1,75 h)
  - Ball occlusion
- 18.11.2022 (6 h)
  - Brick sorting (for transparency rendering)
  - SSAO evaluation
- 19.11.2022 (1 h)
  - Aply SSAO
- 22.11.2022 (1,25 h)
  - Better brick sorting
- 25.11.2022 (3 h)
  - Basic UI library
    - Render texture at specified position and with specified scale
    - Render colored rectangle 
  - Pause screen and pausing

### Collision system and physics
- 25.11.2022 (3,5 h)
  - starting ODE solvers
  - Ball movement and launch
  - Starting collision system
- 1.12.2022 (1,75 h)
  - Finish ode solvers and create tests for them
  - Working on collision system
- 2.12.2022 (1 h)
  - Algorithms with polar coordinates
- 5.12.2022 (3 h)
  - Algorithms with cartesian coordinates
  - Game over and reseting
- 6.12.2022 (4,25 h)
  - Finish ball collisions
- 14.12.2022 (1 h)
  - Brick breaking and falling
- 20.12.2022 (0,5 h)
  - Brick reseting
  - Win condition

### Life counting and scoring system
- 21.12.2022 (2,75 h)
  - Digit rendering
  - UI Canvas begin
- 26.12.2022 (2 h)
  - Finalize UI Canvas
  - Number rendering
- 27.12.2022 (3,5 h)
  - Split game logic to several managers
- 28.12.2022 (1,75 h)
  - Move rendering logic to render manager
  - Add UI for live counting and score
  - Live counting
- 29.12.2022 (2 h)
  - Remove Canvas system
  - Score counting
  - Brick reset, when all destroyed
  - Improve ball alpha masking

### The durability of bricks
- 30.12.2022 (1 h)
  - Brick durability
  - Color switchnig

### Advanced physics
- 30.12.2022 (1 h)
  - Ball acceleration
  - Paddle-ball collision dependent on paddle rotation
- 2.1.2023 (0,5 h)
  - Speedup area

### Final touches
- 3.1.2023 (2,5 h)
  - Rewrite ball physics and fix some issues
- 4.1.2023 (0,5 h)
  - Change color scheme
- 5.1.2023 (0,5 h)
  - Check requirements

## Total time - about 120 hours