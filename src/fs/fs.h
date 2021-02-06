#include <stdint.h>

namespace fs
{

    struct dirent // One of these is returned by the readdir call, according to POSIX.
    {
        char name[128]; // Filename.
        uint32_t ino;   // Inode number. Required by POSIX.
    };

    struct node_t
    {
        char name[128];  // The filename.
        uint32_t mask;   // The permissions mask.
        uint32_t uid;    // The owning user.
        uint32_t gid;    // The owning group.
        uint32_t flags;  // Includes the node type. See #defines above.
        uint32_t inode;  // This is device-specific - provides a way for a filesystem to identify files.
        uint32_t length; // Size of the file, in bytes.
        uint32_t impl;   // An implementation-defined number.
        uint32_t (*read)(node_t, uint32_t, uint32_t, uint8_t *);
        uint32_t (*write)(node_t, uint32_t, uint32_t, uint8_t *);
        void (*open)(node_t *);
        void (*close)(node_t *);
        dirent *(*readdir)(node_t *, uint32_t);
        node_t *(*finddir)(node_t *, char *name);
        node_t *ptr; // Used by mountpoints and symlinks.
    };
} // namespace fs
