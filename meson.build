project('AquaticRPG', 'cpp',
  version : '1.0',
  default_options : ['warning_level=3', 'cpp_std=c++20']
)

# Homebrew paths (Apple Silicon)
sfml_include = include_directories('/opt/homebrew/include')
sfml_lib_dir = '/opt/homebrew/lib'

sfml_modules = ['graphics', 'window', 'system', 'audio']

# Build link arguments
link_args = []
foreach mod : sfml_modules
  link_args += ['-L' + sfml_lib_dir, '-lsfml-' + mod]
endforeach

# Create dependency object for SFML
sfml_dep = declare_dependency(
  include_directories: sfml_include,
  link_args: link_args
)

# Source files
srcs = ['src/main.cpp']

# Executable
executable('AquaticRPG',
  srcs,
  dependencies: [sfml_dep],
  include_directories: ['src'],
  install: true
)