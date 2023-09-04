# PK2 JSON Sprite server
Possible backend to future web-based sprite editor.
To compile:
> make all

To run:
> export PK2_SPRITE_PATH=your_pk2_directory/res/sprites
> ./server.x

# Requests
To obtain all the sprites in one large JSON list:
> GET /api/sprites

To obtain only one particular sprite in sigle JSON object (for example pig.spr):
> GET /api/sprites?name=pig
