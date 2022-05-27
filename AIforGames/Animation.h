#pragma once
#include <raylib.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

template<typename T>
struct Resource{
	template<typename... Args>
	static T* Loader(const char*) { return T{ 0 }; }
	static void Unloader(T*& ref) { ref = T{ 0 }; }
};

template<>
struct Resource<Texture2D> {
	static Texture2D Loader(const char* f) { return LoadTexture(f); }
	static void Unloader(Texture2D& ref) { UnloadTexture(ref); }
};





class ResourceManager
{
private:
	ResourceManager() {};
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	
	template<typename T>
	class Unloader
	{
	private:
		T& container;
	public:
		Unloader(T& c) : container{ c } {};
		~Unloader() {
			for (auto& i : container)
			{
				Resource<T::value_type::second_type>::Unloader(i.second);
			}
		}
	};
	
public:
	//"get" retrieves a resource, but if it doesn't exist, it constructs a new resource using the provided arguments.
	template<typename T,typename... Args>
	static T& get(const std::string& n,Args... defaultArgs) {
		static std::unordered_map<std::string, T> resources;
		static Unloader<std::unordered_map<std::string, T>> unloader(resources);

		auto it = resources.find(n);
		if (it == resources.end()) {
			resources[n] = Resource<T>::Loader(defaultArgs...);
		}
		return resources[n];
	}
};



class Animation
{
private:
	Texture image;
	Rectangle drawSize;
	std::vector<Rectangle> frames;
	float fps = 25.0f;

public:
	Animation() = delete;
	
	Animation(const Animation& other) = delete;

	~Animation() {
		UnloadTexture(image);
	}

	Animation(Rectangle s, const std::string& filename) : drawSize{ s }
	{
		std::ifstream file{ filename };
		if (!file) {
			throw std::runtime_error{ "Couldn't load " + filename };
		}

		//Get texture
		std::string texture;
		std::getline(file,texture);

		// LoadTexture
		image = LoadTexture(texture.c_str());//ResourceManager::get<Texture2D>(texture.c_str(),texture.c_str());

		//Get timing
		file >> fps;

		//get sizes
		Vector2 frameSize;
		file >> frameSize.x;
		file >> frameSize.y;

		//read coordinates
		Rectangle current{ 0,0,frameSize.x,frameSize.y };
		while (file >> current.x) {
			file >> current.y;
			current.x *= frameSize.x;
			current.y *= frameSize.y;
			frames.push_back(current);
		}
	}
public:
	void Draw(Vector2 position, float degrees, const Color& tint = Color{ 255,255,255,255 }) {
		//get rectangle
		int i = (int)(GetTime() * fps) % frames.size();
		
		DrawTexturePro(
			image,
			frames[i],
			Rectangle{position.x,position.y,drawSize.width,drawSize.height }
			,{ drawSize.width/2,drawSize.height/2}
			,degrees,
			tint
		);
	}
};

template<>
struct Resource<Animation*> {
	static Animation* Loader(Rectangle& r, const char* f) { return new Animation{ r, f }; }
	static void Unloader(Animation* ref) { delete ref; }
};

