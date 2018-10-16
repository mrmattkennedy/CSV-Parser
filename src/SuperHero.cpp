#include <string>
#include "SuperHero.h"

/**********************************************************************
 * Implementation of SuperHero constructor. Takes in 13 arguments,
 * and sets the corresponding values.
 *
 * @param page-id
 * @param name
 * @param urlslug
 * @param id
 * @param alignment
 * @param eye_color
 * @param hair_color
 * @param sex
 * @param gsm
 * @param alive
 * @param appearances
 * @param first_appearance
 * @param year
 *********************************************************************/
SuperHero::SuperHero(int page_id,
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
	int year) {
	
	this->page_id 	= page_id;
	this->name 	= name;
	this->urlslug 	= urlslug;
	this->id 	= id;
	this->alignment = alignment;
	this->eye_color = eye_color;
	this->hair_color= hair_color;
	this->sex	= sex;
	this->gsm	= gsm;
	this->alive	= alive;
	this->appearances = appearances;
	this->first_appearance = first_appearance;
	this->year 	= year;
	
}

/**********************************************************************
 * All the getters for each variable in SuperHero class.
 *********************************************************************/
int SuperHero::get_page_id()			const	{return page_id;}
std::string SuperHero::get_name()		const	{return name;}
std::string SuperHero::get_urlslug()		const	{return urlslug;}
std::string SuperHero::get_id()			const	{return id;}
std::string SuperHero::get_alignment()		const	{return alignment;}
char SuperHero::get_eye_color()			const	{return eye_color;}
char SuperHero::get_hair_color()		const	{return hair_color;}
char SuperHero::get_sex()			const	{return sex;}
std::string SuperHero::get_gsm()		const	{return gsm;}
int SuperHero::get_alive()			const	{return alive;}
int SuperHero::get_appearances()		const	{return appearances;}
std::string SuperHero::get_first_appearance()	const	{return first_appearance;}
int SuperHero::get_year()			const	{return year;}




