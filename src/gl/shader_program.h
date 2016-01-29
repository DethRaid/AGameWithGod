//
// Created by David on 27-Jan-16.
//

#ifndef AGAMEWITHGOD_SHADER_H
#define AGAMEWITHGOD_SHADER_H

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include <gl/glm/glm.hpp>
#include "../glad/glad.h"

class missing_required_shader_exception : public std::invalid_argument {
public:
    missing_required_shader_exception(const std::string & what_arg);
    missing_required_shader_exception(const char * what_arg);
};

class uniform_not_found : public std::invalid_argument {
public:
    uniform_not_found(const std::string & what_arg);
    uniform_not_found(const char * what_arg);
};

class shader_compilation_failed_exception : public std::exception {
public:
    shader_compilation_failed_exception(char * msg);

    const char *what() const noexcept {
        // I don't like that this is inplace, but this works
        return msg.c_str();
    }

private:
    std::string msg;
};

class program_link_failed_exception : public std::exception {
public:
    program_link_failed_exception(char * msg);

    const char *what() const noexcept {
        // I don't like that this is inplace, but this works
        return msg.c_str();
    }

private:
    std::string msg;
};

class shader_program {
public:
    /*!
     * \brief Initializes this shader with the shader source at shader_path
     *
     * Note that shader_path shouldn't have any .frag or .vert or anything. Rather, the shader will look for the .vert
     * and .frag files, loading them if found and throwing a missing_required_shader_exception otherwise
     */
    shader_program(std::string shader_path);

    /*!
     * \brief Tells OpenGl to unse this shader for rendering
     */
    void bind();

    /*!
     * \brief Uploads the given mat4 to the specified uniform variable
     *
     * If the given uniform isn't found, throws a uniform_not_found exception
     */
    void set_uniform(std::string name, glm::mat4 value);

    const bool operator==(const shader_program & other) const;
    const bool operator!=(const shader_program & other) const;
private:
    GLuint gl_name;
    std::unordered_map<std::string, GLuint> uniform_locations;
    std::vector<std::string> uniform_names;

    /*!
     * \brief Loads the veretx file from the given file name
     *
     * Also parses the vertex file to try and find any uniforms
     *
     * \param vertex_file_name The path to the vertex file relative to the program's working directory
     *
     * \return The OpenGL name for the vertex shader
     */
    GLuint load_vertex_shader(const std::string vertex_file_name);

    /*!
     * \brief Loads the fragment file from the given file name
     *
     * Also parses the fragment file to try and find any uniforms
     *
     * \param fragment_file_name The path to the fragment file relative to the program's working directory
     *
     * \return The OpenGL name for the fragment shader
     */
    GLuint load_fragment_shader(const std::string fragment_file_name);

    /*!
     * \brief Loads the shader source from the given file, checking for uniforma
     *
     * \param filename The path to the shader file
     *
     * \return The full text of the shader file
     */
    std::string read_shader_file(const std::string & filename);

    /*!
     * \brief Checks if the given line is a uniform variable declaration, extracting the uniform name if so
     *
     * The name of any found uniform variable is written to the uniform_names array
     *
     * \param line The line to check for uniform variables
     */
    void check_for_uniforms(const std::string &line);

    /*!
     * \brief Checks the compilation status of the given shader
     *
     * If there are any compilation messages, prints them to the output log
     *
     * If the shader compiled fine, they're written to the INFO log level. If there was a compilation error, any
     * compilation messages are written to the ERROR log level and a shader_compilation_failed_exceptino is thrown
     *
     * \param shader_name The OpenGL name of the shader to check the compilatino status of
     */
    void check_compilation_errors(GLuint shader_name);

    /*!
     * \brief Compiles the given shader with the given source code
     *
     * \param shader_source_code The full source of the shader to compile
     * \param gl_shader_name The OpenGL name for the shader to compile
     */
    void compile_shader(const std::string &shader_source_code, GLuint gl_shader_name);

    /*!
     * \brief Gets the uniform location of all the found uniforms, writing the locations to the uniform_locations map
     */
    void generate_uniform_map();
};


#endif //AGAMEWITHGOD_SHADER_H
