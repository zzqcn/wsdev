project('wsdev', 'c',
    default_options: [
        'buildtype=debug',
        'b_lundef=false'
    ],
)

if get_option('buildtype').startswith('debug')
    add_project_arguments('-DDEBUG', language: 'c')
endif
add_project_arguments('-Wno-unused-function', language: 'c')

cc = meson.get_compiler('c')
wsdev_conf = configuration_data()
wsdev_headers = []
wsdev_libraries = []
wsdev_extra_ldflags = []

wireshark = declare_dependency(
    include_directories: [
        '@0@'.format(get_option('wireshark_src_dir')),
    ],
    link_args: [
        '-L@0@'.format(get_option('wireshark_lib_dir')),
        '-lwireshark',
        '-lwiretap',
        '-lwsutil',
    ]
)

wsdev_depends = [
    dependency('glib-2.0'),
    dependency('gobject-2.0'),
    wireshark,
]

wsdev_inc = [
    '.',
]

subdir('hello_glib')
subdir('hello_wireshark')