//
// Created by David on 27-Jan-16.
//

#include "shader_program.h"

#include <fstream>
#include <easylogging++.h>

/* Exceptions */
missing_required_shader_exception::missing_required_shader_exception(const std::string &what_arg) :
        std::invalid_argument(what_arg) { }

missing_required_shader_exception::missing_required_shader_exception(const char *what_arg) :
        std::invalid_argument(what_arg) { }

uniform_not_found::uniform_not_found(const std::string &what_arg) :
        std::invalid_argument(what_arg) { }

uniform_not_found::uniform_not_found(const char *what_arg) :
        std::invalid_argument(what_arg) { }

shader_compilation_failed_exception::shader_compilation_failed_exception(char *msg) {
    this->msg = std::string(msg);
}

program_link_failed_exception::program_link_failed_exception(char *msg) {
    this->msg = std::string(msg);
}


/* shader_program */

shader_program::shader_program(std::string shader_path) {
    // Load the vertex and fragment shaders
    GLuint vertex_shader_id = load_vertex_shader(shader_path + ".vert");
    GLuint fragment_shader_id = load_fragment_shader(shader_path + ".frag");

    LOG(DEBUG) << "Vertex and fragment shaders loaded";

    // Link the program
    gl_name = glCreateProgram();
    glAttachShader(gl_name, vertex_shader_id);
    glAttachShader(gl_name, fragment_shader_id);
    glLinkProgram(gl_name);

    LOG(DEBUG) << "Shader submitted for linking";

    // Check for errors
    GLint link_succeeded = GL_FALSE;
    GLint info_log_length;

    glGetProgramiv(gl_name, GL_LINK_STATUS, &link_succeeded);
    glGetProgramiv(gl_name, GL_INFO_LOG_LENGTH, &info_log_length);

    if(info_log_length > 0) {
        char log[info_log_length + 1];
        glGetProgramInfoLog(gl_name, info_log_length, NULL, log);

        if(link_succeeded) {
            LOG(INFO) << "Program link log:\n" << log;
        } else {
            LOG(ERROR) << "Program link log:\n" << log;
            throw program_link_failed_exception(log);
        }
    }

    generate_uniform_map();
}

const bool shader_program::operator==(const shader_program &other) const {
    return gl_name == other.gl_name;
}

const bool shader_program::operator!=(const shader_program &other) const {
    return !(*this == other);
}

/* Private methods */

GLuint shader_program::load_vertex_shader(const std::string vertex_file_name) {
    // Try to open the vertex shader file
    std::string shader_source_code = read_shader_file(vertex_file_name);

    LOG(DEBUG) << "Vertex file loaded into RAM";

    GLuint vertex_shader_name = glCreateShader(GL_VERTEX_SHADER);
    LOG(DEBUG) << "Vertex shader create in OpenGL";

    compile_shader(shader_source_code, vertex_shader_name);

    return vertex_shader_name;
}

GLuint shader_program::load_fragment_shader(const std::string fragment_file_name) {
    std::string shader_source_code = read_shader_file(fragment_file_name);

    LOG(DEBUG) << "Fragment file loaded into RAM";

    GLuint fragment_shader_name = glCreateShader(GL_FRAGMENT_SHADER);

    LOG(DEBUG) << "Fragment shader created in OpenGL";

    compile_shader(shader_source_code, fragment_shader_name);

    return fragment_shader_name;
}

void shader_program::compile_shader(const std::string &shader_source_code, GLuint gl_shader_name) {
    const char * vertex_source_pointer = shader_source_code.c_str();
    glShaderSource(gl_shader_name, 1, &vertex_source_pointer, NULL);
    glCompileShader(gl_shader_name);

    LOG(DEBUG) << "Shader submitted for compilation";

    check_compilation_errors(gl_shader_name);
}

void shader_program::check_for_uniforms(const std::string &line) {
    if(line.find("uniform") == 0) {
        // We want the third word
        size_t start_pos = line.find(' ', 9) + 1;
        size_t end_pos = line.find(';') - 1;

        std::string uniform_name = line.substr(start_pos, end_pos - start_pos);

        LOG(TRACE) << "Extracted uniform " << uniform_name;
        uniform_names.push_back(uniform_name);
    }
}

void shader_program::check_compilation_errors(GLuint shader_name) {
    GLint compilation_succeeded = GL_FALSE;
    GLint info_log_length;
    glGetShaderiv(shader_name, GL_COMPILE_STATUS, &compilation_succeeded);
    glGetShaderiv(shader_name, GL_INFO_LOG_LENGTH, &info_log_length);

    if(info_log_length > 0) {
        char error_message[info_log_length + 1];
        glGetShaderInfoLog(shader_name, info_log_length, NULL, &error_message[0]);

        if(compilation_succeeded) {
            LOG(INFO) << "Shader compile log: \n" << error_message;
        } else {
            LOG(ERROR) << "Shader compile log: \n" << error_message;
            throw shader_compilation_failed_exception(error_message);
        }
    }
}

std::string shader_program::read_shader_file(const std::string &filename) {
    std::ifstream vertex_file(filename.c_str(), std::ios::in);
    if(!vertex_file.is_open()) {
        LOG(ERROR) << "Could not open vertex file " << filename;
        throw missing_required_shader_exception(filename);
    }

    LOG(DEBUG) << "Opening vertex shader file " << filename;
    std::string shader_source_code;
    std::string line = "";
    while(getline(vertex_file, line)) {
        // Check the line for uniforms
        check_for_uniforms(line);
        shader_source_code += "\n" + line;
    }

    vertex_file.close();

    return shader_source_code;
}

void shader_program::generate_uniform_map() {
    for(std::string & uniform : uniform_names) {
        GLint uniform_location = glGetUniformLocation(gl_name, uniform.c_str());

        LOG(TRACE) << "Found uniform " << uniform << " at location " << uniform_location;

        uniform_locations[uniform] = uniform_location;
    }
}
