﻿#pragma once

#include <vector>
#include "FontCharacter.hpp"

namespace acid
{
	/// <summary>
	/// During the loading of a text this represents one word in the text.
	/// </summary>
	class ACID_EXPORT FontWord
	{
	private:
		std::vector<FontCharacter> m_characters;
		float m_width;
	public:
		/// <summary>
		/// Creates a new text word.
		/// </summary>
		FontWord();

		/// <summary>
		/// Adds a character to the end of the current word and increases the screen-space width of the word.
		/// </summary>
		/// <param name="character"> The character to be added. </param>
		/// <param name="kerning"> The character kerning. </param>
		/// <returns> {@code true} if the character has successfully been added to the word. </returns>
		bool AddCharacter(const FontCharacter &character, const float &kerning);

		std::vector<FontCharacter> GetCharacters() const { return m_characters; }

		float GetWidth() const { return m_width; }
	};
}
