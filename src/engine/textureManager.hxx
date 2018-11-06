#ifndef TEXTURE_MANAGER_HXX_
#define TEXTURE_MANAGER_HXX_

#include <iostream>
#include <unordered_map>

#include "SDL2/SDL.h"

#include "tile.hxx"

enum ButtonState
{
  BUTTONSTATE_DEFAULT,
  BUTTONSTATE_HOVERING,
  BUTTONSTATE_CLICKED,
  BUTTONSTATE_DISABLED
};

class TextureManager
{
public:
  /// Retrieves Instance of Singleton class Texture Manager
  static TextureManager &Instance()
  {
    static TextureManager instance;
    return instance;
  }

  // Disable copy and assignemnt operators
  TextureManager(TextureManager const &) = delete;
  TextureManager &operator=(TextureManager const &) = delete;

  /** retrieves texture for a tileID */
  SDL_Texture *getTileTexture(const std::string &type, const std::string &orientation = "");
  SDL_Texture *getUITexture(const std::string &uiElement, int buttonState = BUTTONSTATE_DEFAULT);

  /** Retrieves Color of a specific tileID at coordinates with the texture */
  const SDL_Color getPixelColor(const std::string &type, const std::string &orientation, int X, int Y);

private:
  TextureManager();
  ~TextureManager() = default;

  SDL_Renderer *_renderer;
  SDL_Window *_window;

  /** Load Texture in to Texture Map, if an entry for this tile ID does not yet exist.
  Keep in Mind that the texture id is unique and there can't be two textures with the same id.

  If colorkey is set - Use Magic Pink (255,255,0) for transparency
  */
  void loadUITexture();
  void loadTexture(const std::string &type, const std::string &orientation, bool colorKey = false);

  SDL_Surface *createSurfaceFromFile(const std::string &fileName);
  SDL_Texture *createTextureFromSurface(SDL_Surface *surface);

  std::unordered_map<std::string, std::unordered_map<std::string, SDL_Texture *>> _uiTextureMap;

  // Map < type, <map<orientation, Texture>>
  std::unordered_map<std::string, SDL_Texture *> _tileTextureMap;

  /** Keep surfaces in map for collision detection when selecting tiles*/
  std::unordered_map<std::string, SDL_Surface *> _surfaceMap;
};

#endif
