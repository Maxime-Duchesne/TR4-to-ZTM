#ifndef _TR4_TYPES_
#define _TR4_TYPES_

/** \brief 16-bit texture.
  *
  * Each pixel is a colour with the following format.<br>
  * - 1-bit transparency (0 ::= transparent, 1 ::= opaque) (0x8000)
  * - 5-bit red channel (0x7c00)
  * - 5-bit green channel (0x03e0)
  * - 5-bit blue channel (0x001f)
  */
typedef struct tr2_textile16_s
{
    uint16_t pixels[256][256];
} tr2_textile16_t;

/** \brief 32-bit texture.
  *
  * Each pixel is an ABGR value.
  */
typedef struct tr4_textile32_s
{
    uint32_t pixels[256][256];
} tr4_textile32_t;


typedef struct
{
	uint16_t	width;
	uint16_t	height;
	uint16_t    data[512*320];
}	img_t;


/// \brief RGBA colour using float. For single colours.
typedef struct tr5_colour_s
{
    float r;        ///< \brief the red component.
    float g;        ///< \brief the green component.
    float b;        ///< \brief the blue component.
    float a;        ///< \brief the alpha component.
} tr5_colour_t;

/// \brief RGBA colour using bitu8. For palette etc.
typedef struct tr2_colour_s
{
    uint8_t r;        ///< \brief the red component.
    uint8_t g;        ///< \brief the green component.
    uint8_t b;        ///< \brief the blue component.
    uint8_t a;        ///< \brief the alpha component.
} tr2_colour_t;

/// \brief A vertex with x, y and z coordinates.
typedef struct tr5_vertex_s
{
    float x;
    float y;
    float z;
} tr5_vertex_t;

/// \brief Definition for a triangle.
typedef struct tr4_face3_s
{
    uint16_t vertices[3];    ///< index into the appropriate list of vertices.
    uint16_t texture;        /**< \brief object-texture index or colour index.
                               * If the triangle is textured, then this is an index into the object-texture list.
                               * If it's not textured, then the low 8 bit contain the index into the 256 colour palette
                               * and from TR2 on the high 8 bit contain the index into the 16 bit palette.
                               */
    uint16_t lighting;       /**< \brief transparency flag & strength of the hilight (TR4-TR5).
                               * bit0 if set, then alpha channel = intensity (see attribute in tr2_object_texture).<br>
                               * bit1-7 is the strength of the hilight.
                               */
} tr4_face3_t;

/// \brief Definition for a rectangle.
typedef struct tr4_face4_s
{
    uint16_t vertices[4];    ///< index into the appropriate list of vertices.
    uint16_t texture;        /**< \brief object-texture index or colour index.
                               * If the rectangle is textured, then this is an index into the object-texture list.
                               * If it's not textured, then the low 8 bit contain the index into the 256 colour palette
                               * and from TR2 on the high 8 bit contain the index into the 16 bit palette.
                               */
    uint16_t lighting;       /**< \brief transparency flag & strength of the hilight (TR4-TR5).
                               *
                               * In TR4, objects can exhibit some kind of light reflection when seen from some particular angles.
                               * - bit0 if set, then alpha channel = intensity (see attribute in tr2_object_texture).
                               * - bit1-7 is the strength of the hilight.
                               */
} tr4_face4_t;

/** \brief Room portal.
  */
typedef struct tr_room_portal_s
{
    uint16_t adjoining_room;     ///< \brief which room this portal leads to.
    tr5_vertex_t normal;         /**< \brief which way the portal faces.
                                   * the normal points away from the adjacent room.
                                   * to be seen through, it must point toward the viewpoint.
                                   */
    tr5_vertex_t vertices[4];    /**< \brief the corners of this portal.
                                   * the right-hand rule applies with respect to the normal.
                                   * if the right-hand-rule is not followed, the portal will
                                   * contain visual artifacts instead of a viewport to
                                   * AdjoiningRoom.
                                   */
} tr_room_portal_t;

/** \brief Room sector.
  */
typedef struct tr_room_sector_s
{
    uint16_t fd_index;     // Index into FloorData[]
    uint16_t box_index;    // Index into Boxes[]/Zones[] (-1 if none)
    uint8_t room_below;    // The number of the room below this one (-1 or 255 if none)
    int8_t floor;          // Absolute height of floor (multiply by 256 for world coordinates)
    uint8_t room_above;    // The number of the room above this one (-1 or 255 if none)
    int8_t ceiling;        // Absolute height of ceiling (multiply by 256 for world coordinates)
} tr_room_sector_t;

/** \brief Room light.
  */
typedef struct tr5_room_light_s
{
    tr5_vertex_t pos;           // world coords
    tr2_colour_t color;         // three bytes rgb values
    float intensity;            // Calculated intensity
    uint16_t intensity1;        // Light intensity
    uint16_t intensity2;        // Almost always equal to Intensity1 [absent from TR1 data files]
    uint32_t fade1;             // Falloff value 1
    uint32_t fade2;             // Falloff value 2 [absent from TR1 data files]
    uint8_t light_type;         // same as D3D (i.e. 2 is for spotlight)
    uint8_t unknown;            // always 0xff?
    float r_inner;
    float r_outer;
    float length;
    float cutoff;
    tr5_vertex_t dir;           // direction
    tr5_vertex_t pos2;          // world coords
    tr5_vertex_t dir2;          // direction
} tr5_room_light_t;

/** \brief Room sprite.
  */
typedef struct tr_room_sprite_s
{
    int16_t vertex;                 // offset into vertex list
    int16_t texture;                // offset into sprite texture list
} tr_room_sprite_t;

/** \brief Room layer (TR5).
  */
typedef struct tr5_room_layer_s
{
    uint16_t num_vertices;          // number of vertices in this layer (4 bytes)
    uint16_t unknown_l1;
    uint16_t unknown_l2;
    uint16_t num_rectangles;        // number of rectangles in this layer (2 bytes)
    uint16_t num_triangles;         // number of triangles in this layer (2 bytes)
    uint16_t unknown_l3;
    uint16_t unknown_l4;
    //  The following 6 floats (4 bytes each) define the bounding box for the layer
    float bounding_box_x1;
    float bounding_box_y1;
    float bounding_box_z1;
    float bounding_box_x2;
    float bounding_box_y2;
    float bounding_box_z2;
    int16_t unknown_l6a;
    int16_t unknown_l6b;
    int16_t unknown_l7a;
    int16_t unknown_l7b;
    int16_t unknown_l8a;
    int16_t unknown_l8b;
} tr5_room_layer_t;

/** \brief Room vertex.
  */
typedef struct tr5_room_vertex_s
{
    tr5_vertex_t vertex;    // where this vertex lies (relative to tr2_room_info::x/z)
    int16_t lighting1;
    uint16_t attributes;    // A set of flags for special rendering effects [absent from TR1 data files]
    // 0x8000 something to do with water surface
    // 0x4000 under water lighting modulation and
    // movement if viewed from above water surface
    // 0x2000 water/quicksand surface movement
    // 0x0010 "normal"
    int16_t lighting2;      // Almost always equal to Lighting1 [absent from TR1 data files]
    // TR5 -->
    tr5_vertex_t normal;
    tr5_colour_t colour;    // vertex color ARGB format (4 bytes)
} tr5_room_vertex_t;

typedef struct tr2_room_staticmesh_s
{
    tr5_vertex_t pos;       // world coords
    float rotation;         // high two bits (0xC000) indicate steps of
    // 90 degrees (e.g. (Rotation >> 14) * 90)
    int16_t intensity1;     // Constant lighting; -1 means use mesh lighting
    int16_t intensity2;     // Like Intensity 1, and almost always the same value [absent from TR1 data files]
    uint16_t object_id;     // which StaticMesh item to draw
    tr5_colour_t tint;      // extracted from intensity
} tr2_room_staticmesh_t;


typedef struct tr5_room_s
{
    tr5_vertex_t offset;            ///< \brief offset of room (world coordinates).
    float y_bottom;                 ///< \brief indicates lowest point in room.
    float y_top;                    ///< \brief indicates highest point in room.
    uint32_t num_layers;            // number of layers (pieces) this room (4 bytes)
    tr5_room_layer_t *layers;       // [NumStaticMeshes]list of static meshes
    uint32_t num_vertices;          // number of vertices in the following list
    tr5_room_vertex_t *vertices;    // [NumVertices] list of vertices (relative coordinates)
    uint32_t num_rectangles;        // number of textured rectangles
    tr4_face4_t *rectangles;        // [NumRectangles] list of textured rectangles
    uint32_t num_triangles;         // number of textured triangles
    tr4_face3_t *triangles;         // [NumTriangles] list of textured triangles
    uint32_t num_sprites;           // number of sprites
    tr_room_sprite_t *sprites;      // [NumSprites] list of sprites
    uint16_t num_portals;           // number of visibility portals to other rooms
    tr_room_portal_t *portals;      // [NumPortals] list of visibility portals
    uint16_t num_zsectors;          // "width" of sector list
    uint16_t num_xsectors;          // "height" of sector list
    tr_room_sector_t *sector_list;  // [NumXsectors * NumZsectors] list of sectors
    // in this room
    int16_t intensity1;             // This and the next one only affect externally-lit objects
    int16_t intensity2;             // Almost always the same value as AmbientIntensity1 [absent from TR1 data files]
    int16_t light_mode;             // (present only in TR2: 0 is normal, 1 is flickering(?), 2 and 3 are uncertain)
    uint16_t num_lights;            // number of point lights in this room
    tr5_room_light_t *lights;       // [NumLights] list of point lights
    uint16_t num_static_meshes;     // number of static meshes
    tr2_room_staticmesh_t *static_meshes;    // [NumStaticMeshes]list of static meshes
    int16_t alternate_room;         // number of the room that this room can alternate
    int8_t  alternate_group;        // number of group which is used to switch alternate rooms
    // with (e.g. empty/filled with water is implemented as an empty room that alternates with a full room)

        uint16_t flags;
    // Flag bits:    // 0x0001 - room is filled with water,    // 0x0020 - Lara's ponytail gets blown by the wind;
    // TR1 has only the water flag and the extra unknown flag 0x0100.     // TR3 most likely has flags for "is raining", "is snowing", "water is cold", and "is filled by quicksand", among others.

        uint8_t water_scheme;
    // Water scheme is used with various room options, for example, R and M room flags in TRLE.
    // Also, it specifies lighting scheme, when 0x4000 vertex attribute is set.

    uint8_t reverb_info;

    // Reverb info is used in TR3-5 and contains index that specifies reverb type.
    // 0 - Outside, 1 - Small room, 2 - Medium room, 3 - Large room, 4 - Pipe.

    tr5_colour_t light_colour;    // Present in TR4 and TR5 only

    // TR5 only:

    float room_x;
    float room_z;
    float room_y_bottom;
    float room_y_top;

    uint32_t unknown_r1;
    uint32_t unknown_r2;
    uint32_t unknown_r3;
    uint16_t unknown_r4a;
    uint16_t unknown_r4b;
    uint32_t unknown_r5;
    uint32_t unknown_r6;
} tr5_room_t;

typedef struct tr4_mesh_s
{
    tr5_vertex_t centre;                // This is usually close to the mesh's centroid, and appears to be the center of a sphere used for collision testing.
    int16_t collision_size;             // This appears to be the radius of that aforementioned collisional sphere.
    uint8_t flags;                      // Known flags (&1)
    uint8_t dummy;                      // Unused
    int16_t num_vertices;               // number of vertices in this mesh
    uint32_t vertices_count;
    tr5_vertex_t *vertices;             //[NumVertices]; // list of vertices (relative coordinates)
    int16_t num_normals;                // If positive, number of normals in this mesh.
    // If negative, number of vertex lighting elements (* (-1))
    int16_t num_lights;                 // Engine internal for above
    tr5_vertex_t *normals;              //[NumNormals]; // list of normals (if NumNormals is positive)
    int16_t *lights;                    //[-NumNormals]; // list of light values (if NumNormals is negative)
    int16_t num_textured_rectangles;    // number of textured rectangles in this mesh
    tr4_face4_t *textured_rectangles;   //[NumTexturedRectangles]; // list of textured rectangles
    int16_t num_textured_triangles;      // number of textured triangles in this mesh
    tr4_face3_t *textured_triangles;    //[NumTexturedTriangles]; // list of textured triangles
    // the rest is not present in TR4
    int16_t num_coloured_rectangles;    // number of coloured rectangles in this mesh
    tr4_face4_t *coloured_rectangles;   //[NumColouredRectangles]; // list of coloured rectangles
    int16_t num_coloured_triangles;     // number of coloured triangles in this mesh
    tr4_face3_t *coloured_triangles;    //[NumColouredTriangles]; // list of coloured triangles
} tr4_mesh_t;

typedef struct tr_animation_s
{                // 32 bytes TR1/2/3 40 bytes TR4
    uint32_t frame_offset;      // byte offset into Frames[] (divide by 2 for Frames[i])
    uint8_t frame_rate;         // Engine ticks per frame
    uint8_t frame_size;         // number of bit16's in Frames[] used by this animation
    uint16_t state_id;

    float   speed;
    float   accel;

    float   speed_lateral;      // new in TR4 -->
    float   accel_lateral;      // lateral speed and acceleration.

    uint16_t frame_start;           // first frame in this animation
    uint16_t frame_end;             // last frame in this animation (numframes = (End - Start) + 1)
    uint16_t next_animation;
    uint16_t next_frame;

    uint16_t num_state_changes;
    uint16_t state_change_offset;   // offset into StateChanges[]
    uint16_t num_anim_commands;     // How many of them to use.
    uint16_t anim_command;          // offset into AnimCommand[]
} tr_animation_t;

typedef struct tr_state_change_s
{                        // 6 bytes
    uint16_t state_id;
    uint16_t num_anim_dispatches;       // number of ranges (seems to always be 1..5)
    uint16_t anim_dispatch;             // Offset into AnimDispatches[]
} tr_state_change_t;

typedef struct tr_anim_dispatch_s
{                // 8 bytes
    int16_t low;                // Lowest frame that uses this range
    int16_t high;               // Highest frame (+1?) that uses this range
    int16_t next_animation;     // Animation to dispatch to
    int16_t next_frame;         // Frame offset to dispatch to
} tr_anim_dispatch_t;


typedef struct tr_moveable_s
{                // 18 bytes
    uint32_t object_id;         // Item Identifier (matched in Items[])
    uint16_t num_meshes;        // number of meshes in this object
    uint16_t starting_mesh;     // stating mesh (offset into MeshPointers[])
    uint32_t mesh_tree_index;   // offset into MeshTree[]
    uint32_t frame_offset;      // byte offset into Frames[] (divide by 2 for Frames[i])
    uint32_t frame_index;
    uint16_t animation_index;   // offset into Animations[]
} tr_moveable_t;

typedef struct tr_staticmesh_s
{                    // 32 bytes
    uint32_t object_id;             // Object Identifier (matched in Items[])
    uint16_t mesh;                  // mesh (offset into MeshPointers[])
    tr5_vertex_t visibility_box[2];
    tr5_vertex_t collision_box[2];
    uint16_t flags;                 // Meaning uncertain; it is usually 2, and is 3 for objects Lara can travel through,
    // like TR2's skeletons and underwater vegetation
} tr_staticmesh_t;

typedef struct tr_sprite_sequence_s
{           // 8 bytes
    int32_t object_id;     // Item identifier (matched in Items[])
    int16_t length;        // negative of "how many sprites are in this sequence"
    int16_t offset;        // where (in sprite texture list) this sequence starts
} tr_sprite_sequence_t;

typedef struct tr_sprite_texture_s
{               // 16 bytes
    uint16_t        tile;
    int16_t         x0;        // tex coords
    int16_t         y0;        //
    int16_t         x1;        //
    int16_t         y1;        //

    int16_t         left_side;
    int16_t         top_side;
    int16_t         right_side;
    int16_t         bottom_side;
} tr_sprite_texture_t;

typedef struct tr_camera_s
{
    int32_t x;
    int32_t y;
    int32_t z;
    int16_t room;
    uint16_t unknown1;    // correlates to Boxes[]? Zones[]?
} tr_camera_t;

typedef struct tr4_flyby_camera_s
{
    int32_t pos_x;
    int32_t pos_y;
    int32_t pos_z;
    int32_t target_x;
    int32_t target_y;
    int32_t target_z;
    uint8_t sequence;
    uint8_t index;

    uint16_t fov;
    uint16_t roll;
    uint16_t timer;
    uint16_t speed;
    uint16_t flags;

    int32_t room_id;
} tr4_flyby_camera_t;

typedef struct tr_sound_source_s
{
    int32_t x;              // absolute X position of sound source (world coordinates)
    int32_t y;              // absolute Y position of sound source (world coordinates)
    int32_t z;              // absolute Z position of sound source (world coordinates)
    uint16_t sound_id;      // internal sound index
    uint16_t flags;         // 0x40, 0x80, or 0xc0
} tr_sound_source_t;

typedef struct tr_box_s
{            // 8 bytes [TR1: 20 bytes] In TR1, the first four are bit32's instead of bitu8's, and are not scaled.
    uint32_t zmin;          // sectors (* 1024 units)
    uint32_t zmax;
    uint32_t xmin;
    uint32_t xmax;
    int16_t true_floor;     // Y value (no scaling)
    uint16_t overlap_index; // index into Overlaps[]. The high bit is sometimes set;
    // occurs in front of swinging doors and the like.
} tr_box_t;

typedef struct tr4_object_texture_vert_s
{            // 4 bytes
    int8_t xcoordinate;     // 1 if Xpixel is the low value, -1 if Xpixel is the high value in the object texture
    uint8_t xpixel;
    int8_t ycoordinate;     // 1 if Ypixel is the low value, -1 if Ypixel is the high value in the object texture
    uint8_t ypixel;
} tr4_object_texture_vert_t;


typedef struct tr4_object_texture_s
{                    // 38 bytes TR4 - 20 in TR1/2/3
    uint16_t transparency_flags;    // 0 means that a texture is all-opaque, and that transparency
    // information is ignored.
    // 1 means that transparency information is used. In 8-bit colour,
    // index 0 is the transparent colour, while in 16-bit colour, the
    // top bit (0x8000) is the alpha channel (1 = opaque, 0 = transparent).
    // 2 (only in TR3) means that the opacity (alpha) is equal to the intensity;
    // the brighter the colour, the more opaque it is. The intensity is probably calculated
    // as the maximum of the individual color values.
    uint16_t tile_and_flag;                     // index into textile list
    uint16_t flags;                             // TR4
    tr4_object_texture_vert_t vertices[4];      // the four corners of the texture
    uint32_t unknown1;                          // TR4
    uint32_t unknown2;                          // TR4
    uint32_t x_size;                            // TR4
    uint32_t y_size;                            // TR4
} tr4_object_texture_t;

typedef struct tr2_item_s
{           // 24 bytes [TR1: 22 bytes]
    int16_t object_id;     // Object Identifier (matched in Moveables[], or SpriteSequences[], as appropriate)
    int16_t room;          // which room contains this item
    tr5_vertex_t pos;      // world coords
    uint16_t rotation;        // ((0xc000 >> 14) * 90) degrees
    int16_t intensity1;    // (constant lighting; -1 means use mesh lighting)
    int16_t intensity2;    // Like Intensity1, and almost always with the same value. [absent from TR1 data files]
    int16_t ocb;           // Object code bit - used for altering entity behaviour. Only in TR4-5.
    uint16_t flags;        // 0x0100 indicates "initially invisible", 0x3e00 is Activation Mask
    // 0x3e00 indicates "open" or "activated";  these can be XORed with
    // related FloorData::FDlist fields (e.g. for switches)
} tr2_item_t;

typedef struct tr4_ai_object_s
{
    uint16_t object_id;    // the objectID from the AI object (AI_FOLLOW is 402)
    uint16_t room;
    int32_t x;
    int32_t y;
    int32_t z;
    uint16_t ocb;
    uint16_t flags;        // The trigger flags (button 1-5, first button has value 2)
    int32_t angle;
} tr4_ai_object_t;

struct tr4_level_load
{
    uint32_t Version;
    uint16_t NumRoomTextiles;
    uint16_t NumObjTextiles;
    uint16_t NumBumpTextiles;
    uint16_t NumMiscTextiles;
    uint32_t Textile32_UncompSize;
    uint32_t Textile32_CompSize;
    //uint8_t * Textile32_Compressed;
    uint32_t Textile32Misc_Uncompressed;
    uint32_t Textile32Misc_CompSize;
    uint32_t TotalTextile32;
   // uint8_t * Textile32Misc_Compressed;
    uint32_t Textile16_UncompSize;
    uint32_t Textile16_CompSize;
   // uint8_t * Textile16_Compressed;
    tr4_textile32_t * Textile32;
    tr2_textile16_t * Textile16;

    uint32_t LevelData_UncompSize;
    uint32_t LevelData_CompSize;
    uint8_t * LevelData_Compressed;  //Which will add a ton of important info...

    uint32_t    numRooms;
    tr5_room_t * Rooms;

    uint32_t    NumFloorData; // number of floor data uint16_t's to follow (4 bytes)
    uint16_t  * FloorData; // floor data (NumFloorData * 2 bytes)
         /*       this->floor_data_size = 0;          // destroyed
            this->floor_data = NULL;            // destroyed
            this->mesh_indices_count = 0;       // destroyed
            this->mesh_indices = NULL;          // destroyed*/

    uint32_t meshes_count; // number of uint16_t's of mesh data to follow (=Meshes[]) (4 bytes)
    tr4_mesh_t * Meshes; //[NumMeshPointers]; // note that NumMeshPointers comes AFTER Meshes[]

    uint32_t mesh_indices_count; // number of mesh pointers to follow (4 bytes)
    uint32_t * mesh_indices; //[NumMeshPointers]; // mesh pointer list (NumMeshPointers * 4 bytes)

    uint32_t  animations_count;
    tr_animation_t * animations;


    uint32_t   frame_data_size;
    uint16_t * frame_data;

    uint32_t moveables_count;
    tr_moveable_t * moveables;

    uint32_t static_meshes_count;
    tr_staticmesh_t * static_meshes;

    uint32_t sprite_textures_count;
    tr_sprite_texture_t * sprite_textures;

    uint32_t sprite_sequences_count;
    tr_sprite_sequence_t * sprite_sequences;

    uint32_t cameras_count;
    tr_camera_t * cameras;

    uint32_t flyby_cameras_count;
    tr4_flyby_camera_t * flyby_cameras;

    uint32_t sound_sources_count;
    tr_sound_source_t * sound_sources;

    uint32_t boxes_count;
    tr_box_t * boxes; /**Important**/

    uint32_t overlaps_count;
    uint16_t * overlaps;

    uint32_t animated_textures_count;

    uint8_t animated_textures_uv_count;

    uint32_t object_textures_count;
    tr4_object_texture_t * object_textures;


    uint32_t items_count;
    tr2_item_t * items;

    uint32_t ai_objects_count;
    tr4_ai_object_t * ai_objects;


};

#endif // _TR4_TYPES_
