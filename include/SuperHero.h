#ifndef HEADER_GUARD
#define HEADER_GUARD
#include <string>

/**********************************************************************
 * SuperHero class. Contains 13 instance variables which describe the
 * superhero object.
 *
 * @author Matt Kennedy
 *********************************************************************/
class SuperHero {
	public:
		SuperHero(int page_id,
			std::string name,
			std::string urlslug,
			std::string id,
			std::string alignment,
			char eye_color,
			char hair_color,
			char sex,
			std::string gsm,
			int alive,
			int appearances,
			std::string first_appearance,
			int year);

		int get_page_id() 			const;
		std::string get_name() 			const;
		std::string get_urlslug() 		const;
		std::string get_id() 			const;
		std::string get_alignment()		const;
		char get_eye_color()			const;
		char get_hair_color()			const;
		char get_sex()				const;
		std::string get_gsm()			const;
		int get_alive()				const;
		int get_appearances()			const;
		std::string get_first_appearance()	const;
		int get_year()				const;
	private:
		int page_id;
		std::string name;
		std::string urlslug;
		std::string id;
		std::string alignment;
		char eye_color;
		char hair_color;
		char sex;
		std::string gsm;
		int alive;
		int appearances;
		std::string first_appearance;
		int year;
	};
#endif
