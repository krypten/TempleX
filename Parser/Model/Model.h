/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <string>

#include "../Parser.h"

class Model {
	public:
		enum ModelValueType {
			ModelValueInt,
			ModelValueDouble,
			ModelValueString,
			ModelValueArray
		};

		typedef std::vector<Model> ModelArray;

	private:

		TEXT key;
		ModelValueType valueType;
		union {
			int modelInt;
			double modelDouble;

			TEXT * modelString;
			ModelArray * modelArray;
		} value;

	public:
		// getter const
		TEXT getKey() const;
		ModelValueType getValueType() const;
		void getValue(ModelArray& mArray, bool& error) const;
		void getValue(TEXT& mString, bool& error) const;
		void getValue(double& mDouble, bool& error) const;
		void getValue(int& mInt, bool& error) const;

		// setter
		void setKey(TEXT key);
		void setValueType(ModelValueType type);
		void setValue(int mInt);
		void setValue(double mDouble);
		void setValue(TEXT* mString);
		void setValue(ModelArray* mArray);
};
#endif // MODEL_H_
