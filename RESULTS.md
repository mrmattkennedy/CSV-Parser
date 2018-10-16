int hash_one(const SuperHero & s){return abs((s.get_page_id() * 54321) %% HASH_SIZE);}
Collisions: 5820


int hash_two(const SuperHero & s)
{
	std::string name = s.get_name();
	char eye = s.get_eye_color();
	char hair = s.get_hair_color();
	char sex = s.get_sex();
	int hash_val = 0;

	for (unsigned int i = 0; i < name.length(); i++)
		hash_val += (int)name.at(i);

	hash_val *= s.get_page_id();
	hash_val += s.get_appearances();
	hash_val+=(int)eye;
	hash_val+=(int)hair;
	hash_val+=(int)sex;
	return abs(hash_val % HASH_SIZE);
}
Collisions: 5872


int hash_three(const SuperHero & s)
{
	int a = 54059;
	int b = 74963;
	long h = 37;
	std::string name = s.get_name();
	for (unsigned  int i = 0; i < name.length(); i++)
		h = (h * a) ^ ((int)(name.at(i)) * b);

	return abs(h % HASH_SIZE);
}
Collisions: 5877
