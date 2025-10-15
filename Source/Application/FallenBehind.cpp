//#include <glad/glad.h>
//#include <Math/Math.h>    
//
//int main(int argc, char* argv[]) {
//    neu::file::SetCurrentDirectory("Assets");
//    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());
//
//    // initialize engine
//    LOG_INFO("initialize engine...");
//    neu::GetEngine().Initialize();
//
//    // initialize scene
//
//
//    SDL_Event e;
//    bool quit = false;
//
//    //open gl initialization
//    std::vector<neu::vec3> points{ {-0.5f, -0.5f, 0}, {0.5f, -0.5f, 0}, {0.0f, -0.5f, 0} };
//    std::vector<neu::vec3> colors{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
//	std::vector<neu::vec2> texcoord{ {0, 0}, {0.5f, 10.f}, {1, 1} };
//
//    struct Vertex {
//        neu::vec3 position;
//		neu::vec3 color;
//		neu::vec2 texcoord;
//    };
//
//    std::vector<Vertex> vertices{
//        { {-0.5f, -0.5f, 0}, {1, 0, 0}, {0, 0} },
//        { {-0.5f, 0.5f , 0}, {0, 1, 0}, {0, 1} },
//	    { {0.5f,  0.5f,  0}, {0, 0, 1}, {1, 1} },
//	    { {0.5f,  -0.5f, 0}, {1, 0, 1}, {1, 0} }
//    };
//
//    std::vector<GLuint> indices{
//        0, 1, 2,
//        0, 2, 3
//	};
//
//	GLuint vbo;
//	glGenBuffers(1, &vbo);
//
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
//
//	//index buffer
//	GLuint ibo;
//	glGenBuffers(1, &ibo);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* indices.size(), indices.data(), GL_STATIC_DRAW);
//
//	//Vertex Array
//	GLuint vao;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
//
//    /*
//    GLuint vbo[3];
//    glGenBuffers(3, vbo);
//
//    //Vertex Buffers
//    //points
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
//
//    //colors
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
//
//	//texcoord
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec2) * texcoord.size(), texcoord.data(), GL_STATIC_DRAW);
//
//    GLuint vao;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//
//    glEnableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//
//    glEnableVertexAttribArray(2);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
//    */
//
//    //vertex shader
//    std::string vs_source;
//    neu::file::ReadTextFile("shaders/basic.vert", vs_source);
//    const char* vs_cstr = vs_source.c_str();
//
//    GLuint vs;
//    vs = glCreateShader(GL_VERTEX_SHADER);
//
//    glShaderSource(vs, 1, &vs_cstr, NULL);
//    glCompileShader(vs);
//
//    int success;
//    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        std::string infoLog(512, '\0');  // pre-allocate space
//        GLsizei length;
//        glGetShaderInfoLog(vs, (GLsizei)infoLog.size(), &length, &infoLog[0]);
//        infoLog.resize(length);
//
//        LOG_WARNING("Shader vs compilation failed: {}", infoLog);
//    }
//
//    //fragment shader
//    std::string fs_source;
//    neu::file::ReadTextFile("shaders/basic.frag", fs_source);
//    const char* fs_cstr = fs_source.c_str();
//
//    GLuint fs;
//    fs = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fs, 1, &fs_cstr, NULL);
//    glCompileShader(fs);
//
//    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        std::string infoLog(512, '\0');  // pre-allocate space
//        GLsizei length;
//        glGetShaderInfoLog(fs, (GLsizei)infoLog.size(), &length, &infoLog[0]);
//        infoLog.resize(length);
//
//        LOG_WARNING("Shader fs compilation failed: {}", infoLog);
//    }
//
//    GLuint program = glCreateProgram();
//    glAttachShader(program, vs);
//    glAttachShader(program, fs);
//    glLinkProgram(program);
//
//	glUseProgram(program);
//
//    //texture
//    neu::res_t<neu::Texture> texture = neu::Resources().Get<neu::Texture>("textures/beast.png");
//
//    GLint uniform = glGetUniformLocation(program, "u_time");
//    ASSERT(uniform != -1);
//
//	GLint tex_uniform = glGetUniformLocation(program, "u_texture");
//	glUniform1i(tex_uniform, texture->m_texture);
//
//
//    // MAIN LOOP
//    while (!quit) {
//        while (SDL_PollEvent(&e)) {
//            if (e.type == SDL_EVENT_QUIT) {
//                quit = true;
//            }
//        }
//
//        // update
//        neu::GetEngine().Update();
//
//        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;
//
//        glUniform1f(uniform, neu::GetEngine().GetTime().GetTime());
//
//        // draw
//        neu::vec3 color{ 0, 0, 0 };
//        neu::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
//
//        neu::vec2 mouse = neu::GetEngine().GetInput().GetMousePosition();
//        neu::vec2 position;
//        float angle = neu::GetEngine().GetTime().GetTime() * 90.0f;
//        float scale = neu::math::Remap(-1.0f, 1.0f, 0.5f, 1.5f, neu::math::sin(neu::GetEngine().GetTime().GetTime()));
//        position.x = neu::math::Remap(0.0f, (float)neu::GetEngine().GetRenderer().GetWidth(), -1.0f, 1.0f, mouse.x);
//        position.y = -neu::math::Remap(0.0f, (float)neu::GetEngine().GetRenderer().GetHeight(), -1.0f, 1.0f, mouse.y);
//
//        neu::GetEngine().GetRenderer().Clear();
//
//		glBindVertexArray(vao);
//		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
//
//        neu::GetEngine().GetRenderer().Present();
//    }
//
//    neu::GetEngine().Shutdown();
//
//	glBindVertexArray(vao);
//	glDeleteVertexArrays(1, &vao);
//
//    return 0;
//}
//
////Vert ------------------------------------------------------------------------------------------------
//#version 460 core
//
//layout(location = 0) in vec3 a_position;
//layout(location = 1) in vec3 a_color;
//layout(location = 2) in vec3 a_textcoord;
//
//out vec3 v_color;
//out vec3 v_textcoord;
//
//uniform float u_time;
//
//void main() {
//    v_color = a_color;
//    v_textcoord = a_textcoord;
//
//    gl_Position = vec4(a_position * sin(u_time), 1.0);
//}
//
////Frag ------------------------------------------------------------------------------------------------
//#version 460 core
//
//in vec3 v_color;
//in vec2 v_textcoord;
//
//out vec4 f_color;
//
//uniform float u_time;
//uniform sampler2D u_texture;
//
//void main() {
//    f_color = texture(u_texture, v_textcoord) * vec4(v_color, 1);
//}
//
//// RENDERER.h --------------------------------------------------------------------------------
//
//#pragma once
//#include <SDL3/SDL.h>
//#include <SDL3_ttf/SDL_ttf.h>
//#include <SDL3_image/SDL_image.h>
//#include <iostream>
//
//namespace neu {
//	/// <summary>
//	/// Main rendering system that manages the SDL window and renderer.
//	/// Provides methods for initializing the graphics system, clearing the screen,
//	/// drawing primitives (lines, points), rendering textures, and presenting frames.
//	/// This class wraps SDL3's rendering functionality with a simplified interface.
//	/// </summary>
//	class Renderer
//	{
//	public:
//		Renderer() = default;
//
//		/// <summary>
//		/// Initializes SDL video and TTF (TrueType font) systems.
//		/// Must be called before creating a window or performing any rendering operations.
//		/// </summary>
//		/// <returns>True if initialization was successful; otherwise, false</returns>
//		bool Initialize();
//
//		/// <summary>
//		/// Shuts down the renderer and cleans up SDL resources.
//		/// Destroys the renderer, window, and quits SDL and TTF systems.
//		/// Should be called during application cleanup.
//		/// </summary>
//		void Shutdown();
//
//		/// <summary>
//		/// Creates a window with the specified properties and an associated renderer.
//		/// Sets up VSync and logical presentation (letterbox scaling) for consistent rendering.
//		/// </summary>
//		/// <param name="name">The title of the window</param>
//		/// <param name="width">The width of the window in pixels</param>
//		/// <param name="height">The height of the window in pixels</param>
//		/// <param name="fullscreen">If true, creates a fullscreen window; otherwise, windowed mode</param>
//		/// <returns>True if the window and renderer were successfully created; otherwise, false</returns>
//		bool CreateWindow(const std::string& name, int width, int height, bool fullscreen = false);
//
//		/// <summary>
//		/// Clears the screen with the current draw color.
//		/// Call this at the beginning of each frame before drawing.
//		/// </summary>
//		void Clear();
//
//		/// <summary>
//		/// Presents the rendered frame to the screen.
//		/// Call this at the end of each frame after all drawing is complete.
//		/// Swaps the back buffer to the front buffer (double buffering).
//		/// </summary>
//		void Present();
//    		
//		/// <summary>
//		/// Gets the width of the window/render target.
//		/// </summary>
//		/// <returns>The width in pixels</returns>
//		int GetWidth() const { return m_width; }
//
//		/// <summary>
//		/// Gets the height of the window/render target.
//		/// </summary>
//		/// <returns>The height in pixels</returns>
//		int GetHeight() const { return m_height; }
//
//	private:
//		// Allow Text and Texture classes to access the SDL renderer for their operations
//		friend class Text;
//		friend class Texture;
//
//		// Dimensions of the render target
//		int m_width{ 0 };
//		int m_height{ 0 };
//
//		// SDL window handle
//		SDL_Window* m_window = nullptr;
//
//		// OpenGL context
//		SDL_GLContext m_context = nullptr;
//	};
//}
//
////RENDERER.CPP--------------------------------------------------------------------------------
//
//#include "Renderer.h"
//#include "Texture.h"
//
//namespace neu {
//    /// <summary>
//    /// Initializes the SDL video subsystem and the SDL_ttf font library.
//    /// This must be called before creating windows or performing any rendering.
//    /// </summary>
//    /// <returns>True if both SDL and TTF were successfully initialized; otherwise, false</returns>
//    bool Renderer::Initialize() {
//        // Initialize SDL video subsystem
//        if (!SDL_Init(SDL_INIT_VIDEO)) {
//            LOG_ERROR("SDL_Init Error: {}", SDL_GetError());
//            return false;
//        }
//
//        // Initialize SDL_ttf for TrueType font rendering
//        if (!TTF_Init()) {
//            LOG_ERROR("TTF_Init Error: {}", SDL_GetError());
//            return false;
//        }
//
//        return true;
//    }
//
//    /// <summary>
//    /// Shuts down the rendering system and releases all SDL resources.
//    /// Quits TTF, destroys the renderer and window, and quits SDL.
//    /// Call this during application cleanup.
//    /// </summary>
//    void Renderer::Shutdown() {
//        TTF_Quit();                         // Shutdown SDL_ttf
//        SDL_DestroyRenderer(m_renderer);    // Destroy the renderer
//        SDL_DestroyWindow(m_window);        // Destroy the window
//        SDL_Quit();                         // Shutdown SDL
//    }
//
//    /// <summary>
//    /// Creates a window and associated renderer with the specified properties.
//    /// Sets up VSync for smooth rendering and logical presentation for resolution-independent scaling.
//    /// The logical presentation uses letterbox mode to maintain aspect ratio.
//    /// </summary>
//    /// <param name="name">The window title displayed in the title bar</param>
//    /// <param name="width">The logical width of the render area in pixels</param>
//    /// <param name="height">The logical height of the render area in pixels</param>
//    /// <param name="fullscreen">If true, creates a fullscreen window; otherwise, windowed mode</param>
//    /// <returns>True if window and renderer creation succeeded; otherwise, false</returns>
//    bool Renderer::CreateWindow(const std::string& name, int width, int height, bool fullscreen) {
//        // Store the logical dimensions
//        m_width = width;
//        m_height = height;
//
//        // Create the SDL window
//        m_window = SDL_CreateWindow(name.c_str(), width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
//        if (m_window == nullptr) {
//            LOG_ERROR("SDL_CreateWindow Error: {}", SDL_GetError());
//            SDL_Quit();
//            return false;
//        }
//
//        // Create the SDL renderer associated with the window
//        m_renderer = SDL_CreateRenderer(m_window, NULL);
//        if (m_renderer == nullptr) {
//            LOG_ERROR("SDL_CreateRenderer Error: {}", SDL_GetError());
//            SDL_DestroyWindow(m_window);
//            SDL_Quit();
//            return false;
//        }
//
//        // Enable VSync (vertical sync) to synchronize rendering with monitor refresh rate
//        // 1 = VSync on, 0 = VSync off
//        SDL_SetRenderVSync(m_renderer, 1);
//
//        // Set up logical presentation for resolution-independent rendering
//        // Letterbox mode adds black bars to maintain aspect ratio when window is resized
//        SDL_SetRenderLogicalPresentation(m_renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
//
//        return true;
//    }
//
//    
//
//    /// <summary>
//    /// Clears the entire render target with the current draw color.
//    /// Call this at the beginning of each frame to clear the previous frame's contents.
//    /// </summary>
//    void Renderer::Clear() {
//		glClear(GL_COLOR_BUFFER_BIT);
//        //SDL_RenderClear(m_renderer);
//    }
//
//    /// <summary>-
//    /// Presents the rendered frame to the screen by swapping buffers.
//    /// Call this at the end of each frame after all drawing operations are complete.
//    /// Uses double buffering: renders to back buffer, then swaps to front buffer for display.
//    /// </summary>
//    void Renderer::Present() {
//		SDL_GL_SwapWindow(m_window);
//        //SDL_RenderPresent(m_renderer);
//    }
//}
//
////MESH.cpp ------------------------------------------------------------------------------------------------
//
//#include "Mesh.h"
//#include "Renderer.h"
//
//namespace neu {
//    bool Mesh::Load(const std::string& filename) {
//
//        std::string buffer;
//        if (!file::ReadTextFile(filename, buffer)) {
//            LOG_ERROR("Could not read file: {}", filename);
//            return false;
//        }
//
//        std::stringstream stream(buffer);
//
//        // read color
//        stream >> m_color;
//
//        // read points
//        vec2 point;
//        while (stream >> point) {
//            m_points.push_back(point);
//        }
//
//        if (!stream.eof()) {
//            LOG_ERROR("Could not parse file: {}", filename);
//            return false;
//        }
//
//        return true;
//    }
//
//    /// <summary>
//    /// Calculates and updates the model's radius as the maximum distance from the origin among all points.
//    /// </summary>
//    void Mesh::CalculateRadius()
//    {
//        m_radius = 0;
//        for (auto& point : m_points) {
//            float length = point.Length();
//            if (length > m_radius) m_radius = length;
//        }
//    }
//}
//
////TEXT.CPP --------------------------------------------------------------------------------
//
//#include "Text.h"
//#include "Font.h"
//#include "Renderer.h"
//
//namespace neu {
//    /// <summary>
//    /// Destroys the Text object and releases its associated SDL texture if it exists.
//    /// </summary>
//    Text::~Text() {
//        if (m_texture) glDeleteTextures(1, &m_texture);
//    }
//
//    /// <summary>
//    /// Creates a texture from the given text string and color using the specified renderer.
//    /// </summary>
//    /// <param name="renderer">Reference to the Renderer object used to create the texture.</param>
//    /// <param name="text">The text string to render.</param>
//    /// <param name="color">The color of the text, represented as a vec3 (RGB components in the range [0, 1]).</param>
//    /// <returns>True if the texture was successfully created; false otherwise.</returns>
//    bool Text::Create(Renderer& renderer, const std::string& text, const vec3& color) {        
//        return true;
//    }    
//
//    void Text::Draw(Renderer& renderer, float x, float y) {        
//	}
//
//}
//
////Texture.h--------------------------------------------------------------------------------
//#pragma once
//#include <glad/glad.h>
//#include "Resources/Resource.h"
//#include "Math/Vector2.h"
//#include <string>
//
//struct SDL_Texture;
//
//namespace neu {
//    /// <summary>
//    /// Represents a 2D texture that can be rendered to the screen.
//    /// This class wraps an SDL_Texture object and manages its lifetime.
//    /// Textures are loaded from image files and stored in GPU memory for efficient rendering.
//    /// Inherits from Resource to support the resource management system.
//    /// </summary>
//    class Texture : public Resource {
//    public:
//        Texture() = default;
//        ~Texture();
//
//        /// <summary>
//        /// Loads an image file and creates a texture for rendering.
//        /// Supports common image formats like PNG, JPG, BMP through SDL_image.
//        /// </summary>
//        /// <param name="filename">Path to the image file (e.g., "assets/textures/player.png")</param>
//        /// <param name="renderer">Reference to the Renderer that will manage this texture</param>
//        /// <returns>True if the texture was successfully loaded; otherwise, false</returns>
//        bool Load(const std::string& filename);
//
//        /// <summary>
//        /// Gets the dimensions of the texture in pixels.
//        /// </summary>
//        /// <returns>A vec2 containing the width and height of the texture</returns>
//        vec2 GetSize() { return m_size; }
//
//        // Allow Renderer class to access the texture for drawing operations
//        friend class Renderer;
//
//		GLuint m_texture = 0;
//    private:
//        GLenum m_target = Gl_TEXTURE_2D;
//
//        // The dimensions of the texture in pixels
//        vec2 m_size{ 0, 0 };
//    };
//}
//
////tEXTURE ANIMATION.CPP--------------------------------------------------------------------------------
//
//#include "TextureAnimation.h"
//
//namespace neu {
//    /// <summary>
//    /// Loads animation data from a JSON configuration file.
//    /// The JSON file defines the sprite sheet layout and animation settings.
//    /// Expected JSON format:
//    /// {
//    ///   "texture_name": "path/to/spritesheet.png",
//    ///   "columns": 4,
//    ///   "rows": 2,
//    ///   "start_frame": 0,
//    ///   "total_frames": 8,
//    ///   "frames_per_second": 10.0,
//    ///   "loop": true
//    /// }
//    /// </summary>
//    /// <param name="filename">Path to the JSON animation configuration file</param>
//    /// <param name="renderer">Reference to the Renderer for loading the texture</param>
//    /// <returns>True if the animation and texture were successfully loaded; otherwise, false</returns>
//    bool TextureAnimation::Load(const std::string& filename, class Renderer& renderer) {
//        // Load the JSON document
//        neu::serial::document_t document;
//        if (!neu::serial::Load(filename, document)) {
//            LOG_ERROR("Could not load TextureAnimation json {}", filename);
//            return false;
//        }
//
//        // Read the texture filename from the JSON
//        std::string texture_name;
//        SERIAL_READ(document, texture_name);
//
//        // Load the sprite sheet texture using the resource manager
//        m_texture = Resources().Get<Texture>(texture_name);
//        if (!m_texture) {
//            LOG_ERROR("Could not load texture in Texture Animation {}", texture_name);
//        }
//
//        // Read animation configuration from JSON
//        SERIAL_READ_NAME(document, "columns", m_columns);           // Grid columns
//        SERIAL_READ_NAME(document, "rows", m_rows);                 // Grid rows
//        SERIAL_READ_NAME(document, "start_frame", m_startFrame);    // Starting frame offset
//        SERIAL_READ_NAME(document, "total_frames", m_totalFrames);  // Number of frames in sequence
//        SERIAL_READ_NAME(document, "frames_per_second", m_framesPerSecond); // Playback speed
//        SERIAL_READ_NAME(document, "loop", m_loop);                 // Loop behavior
//
//        return true;
//    }
//
//    /// <summary>
//    /// Calculates the size of a single animation frame.
//    /// Divides the total texture size by the grid dimensions to get individual frame size.
//    /// </summary>
//    /// <returns>A vec2 containing the frame width and height in pixels</returns>
//    vec2 TextureAnimation::GetSize() const {
//        vec2 size = m_texture->GetSize();
//
//        // Calculate frame size by dividing texture dimensions by grid layout
//        return { size.x / m_columns, size.y / m_rows };
//    }
//
//    /// <summary>
//    /// Calculates the rectangle coordinates for a specific frame in the sprite sheet.
//    /// Frames are indexed left-to-right, top-to-bottom in the grid.
//    /// The calculation accounts for the start_frame offset to support multi-animation sheets.
//    /// </summary>
//    /// <param name="frame">The frame index (0-based) within the animation sequence</param>
//    /// <returns>A rect defining the position and size of the frame in the texture</returns>
//    rect TextureAnimation::GetFrameRect(int frame) const
//    {
//        // Validate frame index and default to frame 0 if out of bounds
//        if (!IsValidFrame(frame)) {
//            LOG_WARNING("Frame is outside bounds {}/{}", frame, m_totalFrames);
//            frame = 0;
//        }
//
//        rect frameRect;
//        vec2 size = GetSize();
//
//        // Set frame dimensions
//        frameRect.w = size.x;
//        frameRect.h = size.y;
//
//        // Calculate frame position in the sprite sheet grid
//        // Add start_frame offset to support multiple animations in one sheet
//        // Use modulo for column (x) and division for row (y) to map 1D index to 2D grid
//        frameRect.x = ((m_startFrame + frame) % m_columns) * frameRect.w;
//        frameRect.y = ((m_startFrame + frame) / m_columns) * frameRect.h;
//
//        return frameRect;
//    }
//}
//
////TEXTURE.CPP--------------------------------------------------------------------------------
//
//#include "Texture.h"
//#include "Renderer.h"
//
//namespace neu {
//    /// <summary>
//    /// Destructor ensures proper cleanup of SDL resources.
//    /// Destroys the SDL texture if it exists, freeing GPU memory.
//    /// </summary>
//    Texture::~Texture() {
//        // If texture exists, destroy texture to free GPU resources
//        if (m_texture) SDL_DestroyTexture(m_texture);
//    }
//
//    /// <summary>
//    /// Loads an image file from disk and creates an SDL texture for rendering.
//    /// The loading process involves two steps:
//    /// 1. Load the image into a CPU-side surface using SDL_image
//    /// 2. Create a GPU-side texture from the surface for efficient rendering
//    /// The surface is freed after texture creation to conserve memory.
//    /// </summary>
//    /// <param name="filename">Path to the image file to load</param>
//    /// <param name="renderer">Reference to the Renderer that provides the SDL_Renderer context</param>
//    /// <returns>True if the texture was successfully loaded and created; otherwise, false</returns>
//    bool Texture::Load(const std::string& filename, Renderer& renderer) {
//        // Load image onto a CPU-side surface
//        // SDL_image supports various formats: PNG, JPG, BMP, GIF, etc.
//        SDL_Surface* surface = IMG_Load(filename.c_str());
//        if (!surface) {
//            LOG_ERROR("Could not load image: {}", filename);
//            return false;
//        }
//
//		SDL_FlipSurface(surface, SDL_FLIP_VERTICAL);
//
//        // Create a GPU-side texture from the surface
//        // The renderer is a friend class, so we can access m_renderer directly
//        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
//
//        // Once texture is created on GPU, the CPU-side surface can be freed
//        // This saves memory as we only need the GPU texture for rendering
//        SDL_DestroySurface(surface);
//
//        if (!m_texture) {
//            LOG_ERROR("Could not create texture: {}", filename);
//            return false;
//        }
//
//        // Query the texture for its dimensions
//        SDL_GetTextureSize(m_texture, &m_size.x, &m_size.y);
//
//        return true;
//    }
//}