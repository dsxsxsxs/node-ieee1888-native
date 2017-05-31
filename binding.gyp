{
  "targets": [
    {
      'target_name': 'libieee1888',
      'type': 'static_library',
      'sources': ["src/ieee1888_XMLgenerator.c", "src/ieee1888_XMLparser.c" ,"src/ieee1888_client.c", "src/ieee1888_object_factory.c" ,"src/ieee1888_server.c", "src/ieee1888_util.c"],
      'direct_dependent_settings': {
        # 'include_dirs': ['./src'],  # dependents need to find cruncher.h.
      },
      'link_settings': {
        'libraries': ['-lpthread'],
      },

    },
    {
      "target_name": "ieee1888",
      "dependencies": ['libieee1888'],
      "sources": ["src/ieee1888.cc", "src/ieee1888Main.cc"],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        './src'
      ],
    }
  ]
}
