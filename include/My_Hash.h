#ifndef INCLUDE_GUARD
#define INCLUDE_GUARD
#define HASH_SIZE 17011
#include <vector>
#include <cmath>
template <typename T>

/**********************************************************************
 * My_Hash class is a representation of a hash. Has a data variable
 * that is a vector of vectors of type T, and can keep track of
 * collisions.
 *
 * @author Matt Kennedy
 *********************************************************************/
class My_Hash {
public:
	/**************************************************************
	 * Constructor. Initializes data as a vector of vectors of
	 * type T.
	 *************************************************************/
	My_Hash()
	{
		std::vector<T> temp;
		for (int i = 0; i < HASH_SIZE; i++)
			data.push_back(temp);	
	}
	
	/**************************************************************
	 * Clears data. I know insert and get were supposed to be
	 * the only public funcs, but I didn't know how to clear data
	 * without calling this func every time insert was called
	 * (which would be over 16,000 times.)
	 *************************************************************/
	void clear_data()
	{
		for (unsigned int i = 0; i < data.size(); i++)
			data[i].clear();
	}

	/**************************************************************
	 * Inserts a given object T into the appropriate vector in
	 * data. Calculates an index given a hash func called hasher,
	 * which returns an int and has a param of const reference T.
	 *
	 * @param const T & s The object of type T to insert.
	 * @param int (*hasher)(const T&) Pointer to the func which
	 * 	will provide a hash index.
	 * @return bool True if collision will occur, false if not.
	 *************************************************************/
	bool insert(const T & s, int (*hasher)(const T&))
	{
		bool collision = false;
		int index = hasher(s);
		if (data[index].size() > 0)
			collision = true;

		data[index].insert(data[index].begin(), s);

		return collision;
	}
	
	/**************************************************************
	 * Gets the reference to an object containing a given name.
	 *
	 * @param const std::string name The name to search for.
	 * @return The object of type T that has the given name.
	 *************************************************************/
	T & get(const std::string name)
	{
		for (int i = 0; i < data.size(); i++)
			for (int j = 0; j < data[i].size; j++)
				if (data[i][j].get_name() == name)
					return data[i][j];
	}

private:
	/* Vector of vectors of type T. */
	std::vector< std::vector<T> > data;
};
#endif
