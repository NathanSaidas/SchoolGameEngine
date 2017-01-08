#ifndef GAME_ENGINE_DIRECTORY_H
#define GAME_ENGINE_DIRECTORY_H

#pragma region CHANGE LOG
/// --	April	9, 2015 - Nathan Hanlan - Added in Directory class to handle basic directory operations.
#pragma endregion

#include "../BasicTypes.h"


namespace Engine
{
	/**
	* This is a utilities class which wraps Directory functions for different platforms.
	*/
	class Directory : public object
	{
		RDECLARE_CLASS(Directory)
	public:
		/**
		* Initializes an empty directory.
		*/
		Directory();
		/**
		* Initializes a directory with the given path
		*/
		Directory(std::string aPath);
		/**
		* Destructor...
		*/
		~Directory();

		/**
		* Traverses back one directory.
		*/
		void Back();
		/**
		* Traverses back aCount directories.
		* @param aCount The amount of time to go back.
		*/
		void Back(int aCount);
		/**
		* Attempts to change to the specified sub-directory.
		* @param aPath The name of the subdirectory.
		* @return Returns true if the change was successful, false if it doesn't exist..
		*/
		bool Change(const std::string & aPath);

		/**
		* Gets the path of the directory.
		* @return Returns the path of the directory.
		*/
		std::string GetPath();
		/**
		* Gets the path of the directory.
		* @return Returns the path of the directory.
		*/
		std::string GetPath() const;
		/**
		* Sets the path of the directory.
		* @param aPath The path of the directory.
		*/
		void SetPath(std::string aPath);

		/**
		* Returns the current operating directory.
		*/
		static Directory GetCurrent();
		/**
		* Returns true if the directory exists.
		*/
		static bool Exists(const Directory & aDirectory);

		//TODO(Nathan): Implement these features.
		//static bool Create(const std::string & aFilename);
		//static bool Delete(const std::string & aFilename);

		//TODO(Nathan): Create an actual file class to handle file operations.
		static bool FileExists(const std::string & aFilename);
		/**
		* The maximum length of chars a directory may be.
		*/
		static const UInt32 MAX_DIRECTORY_LENGTH = 1024;
	private:
		/**
		* The path to the directory.
		*/
		std::string m_Path;

	};

	TYPE_DEFINE(Directory)
}

#endif