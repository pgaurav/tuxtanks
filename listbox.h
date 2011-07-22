#ifndef LISTBOX_H
#define LISTBOX_H
#include <string>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "font.h"
#include "texture.h"

class ListBox
{
	protected:
		int m_w, m_h;
		int m_x, m_y;
		int m_curitem;
		int m_hoveritem;
		std::string m_caption;
		std::vector<std::string> m_items;
		TextureHash m_icons;
		Font *m_font;
		bool m_enabled;
	public:
		ListBox(const std::string& caption, int w = 200, int h = 0);
		void render(int x, int y);
		void addItem(const std::string& item, const std::string& icon);
		void addItem(const std::string& item, int textureid);
		void removeItem(const std::string& item);
		void setChecked(const std::string& item);
		std::string getChecked();
		std::vector<std::string>& getItemArr();
		TextureHash getTextureHash();
		void handleEvents(SDL_Event event);
		bool isEnabled();
		void setEnabled(bool truth);
		virtual ~ListBox();
};

#endif // LISTBOX_H
