/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#include <fstream>
#include <iostream>
#include <sstream>

#include "ConvertUtil.h"

#include "Parser.h"
#include "XML/XmlDOMParser.h"
#include "JSON/JsonDOMParser.h"


#define SSTR(x) dynamic_cast< std::ostringstream & >( \
	( std::ostringstream() << std::dec << x ) ).str()

void ConvertUtil::convertXML2JSON(TEXT xmlInput, Parser::ParseInputType inputType, JsonObject& outNode, bool& error)
{
	Node node;
	Model model;

	XmlParser parser;
	parser.parseXML(xmlInput, inputType, node, error);

	if (error) {
		convertXML2Model(node, model, error);
	} else {
		convertModel2JSON(model, outNode, error);
	}
}

void ConvertUtil::convertJSON2XML(TEXT jsonInput, Parser::ParseInputType inputType, Node& outNode, bool& error)
{
	Model model;
	JsonObject jObject;

	JsonParser jParser;
	jParser.parseJSON(jsonInput, inputType, jObject, error);

	if (error) {
		convertJSON2Model(jObject, model, error);
	} else {
		convertModel2XML(model, outNode, error);
	}
}


void ConvertUtil::convertXML2Model(Node xmlInput, Model model, bool& error)
{
	Model::ModelArray modelArray;
	modelArray.push_back(attributes2Model(xmlInput.getAttributes()));

	model.setKey(xmlInput.getNodeName());
	Node * currChild = xmlInput.getFirstChild();
	Node * lastChild = xmlInput.getLastChild();

	if (currChild == NULL) {
		model.setValueType(Model::ModelValueType::ModelValueString);
		TEXT temp = xmlInput.getData().getValue();
		TEXT * text = new TEXT(temp);
		model.setValue(text);
	} else {
		while (currChild != NULL) {
			Model tempModel;
			convertXML2Model(*currChild, tempModel, error);

			if (error) return;
			modelArray.push_back(tempModel);

			if (currChild == lastChild) {
				currChild = NULL;
			} else {
			}
				currChild = currChild->getNextSibling();
		}
	}
}


void ConvertUtil::convertModel2XML(Model model, Node& outNode, bool& error)
{
	if (error) {
		return ;
	}

	if (model.getKey() == XML_ATTRIBUTE_TAG) {
		// TBD : Internal working exposed
		Model::ModelArray temp;
		model.getValue(temp, error);
		outNode.setAttributes(model2Attributes(temp[0], error));
	} else {
		outNode.setNodeName(model.getKey());
		modelValue2XMLNode(model, outNode, error);
	}
}

void ConvertUtil::modelValue2XMLNode(Model model, Node& outNode, bool& error)
{
	switch(model.getValueType()) {
		case Model::ModelValueType::ModelValueInt :
			{
				int data;
				model.getValue(data, error);
				outNode.setData(SSTR(data));
				break;
			}
		case Model::ModelValueType::ModelValueDouble :
			{
				double data;
				model.getValue(data, error);
				outNode.setData(SSTR(data));
				break;
			}
		case Model::ModelValueType::ModelValueString :
			{
				TEXT data;
				model.getValue(data, error);
				outNode.setData(SSTR(data));
				break;
			}
		case Model::ModelValueType::ModelValueArray :
			{
				Model::ModelArray modelArray;
				model.getValue(modelArray, error);
				for(auto &iModel : modelArray) {
					Node * node = new Node();
					convertModel2XML(iModel, *node, error);
					outNode.addChild(node);
				}
				break;
			}
		default :
			{
				error = true;
				return;
			}
	}
}

void ConvertUtil::convertJSON2Model(JsonObject jsonInput, Model& model, bool& error)
{
	switch(jsonInput.getObjectType()) {
		case JsonObject::JsonObjectType::JSONMap:
			{
				JsonObject::JsonMap jMap;
				Model::ModelArray * mArray = new Model::ModelArray();

				jsonInput.getObject(jMap, error);
				model.setKey(jMap.first);

				Model iModel;
				jsonValue2Model(jMap.second, iModel, error);
				mArray->push_back(iModel);

				model.setValueType(Model::ModelValueType::ModelValueArray);
				model.setValue(mArray);
				break;
			}
		case JsonObject::JsonObjectType::JSONArray:
			{
				JsonObject::JsonArray jArray;
				jsonInput.getObject(jArray, error);

				model.setKey(JSON_ARRAY_TAG);

				Model::ModelArray * mArray = new Model::ModelArray();
				for (auto &val : jArray) {
					Model iModel;
					jsonValue2Model(val, iModel, error);
					mArray->push_back(iModel);
				}

				model.setValueType(Model::ModelValueType::ModelValueArray);
				model.setValue(mArray);
				break;
			}
		default:
			{
				error = true;
				return;
			}
	}
}

void ConvertUtil::convertModel2JSON(Model model, JsonObject& outNode, bool& error)
{
	if (error) {
		return ;
	}

	JsonValue value;
	switch(model.getValueType()) {
		case Model::ModelValueType::ModelValueInt :
			{
				int data;
				model.getValue(data, error);
				//value.setValue(std::string(SSTR(data)));
				break;
			}
		case Model::ModelValueType::ModelValueDouble :
			{
				double data;
				model.getValue(data, error);
				//value.setValue(SSTR(data));
				break;
			}
		case Model::ModelValueType::ModelValueString :
			{
				TEXT data;
				model.getValue(data, error);
				//value.setValue(SSTR(data));
				break;
			}
		case Model::ModelValueType::ModelValueArray :
			{
				Model::ModelArray modelArray;

				JsonValue jValue;
				JsonObject::JsonArray * jArray = new JsonObject::JsonArray();
				JsonObject * jObject = new JsonObject();

				model.getValue(modelArray, error);
				for(auto &iModel : modelArray) {
					JsonObject * obj = new JsonObject();
					convertModel2JSON(iModel, *obj, error);
					jValue.setValue(obj);
					JsonObject::assignArray(jArray, jValue);
				}
				jObject->setObject(jArray);
				value.setValue(jObject);
				break;
			}
		default :
			{
				error = true;
				return;
			}
	}

	JsonObject::JsonMap* jMap = new JsonObject::JsonMap();
	JsonObject::assignMap(jMap, model.getKey(), value);
}

Model ConvertUtil::attributes2Model(Attribute attributes)
{
	Model model;
	model.setKey(XML_ATTRIBUTE_TAG);

	Model::ModelArray * mArray = new Model::ModelArray();

	for (auto &attribute : attributes.getAttributeMap()) {
		Model temp;
		temp.setKey(attribute.first);
		temp.setValueType(Model::ModelValueType::ModelValueString);
		temp.setValue(new std::string(attributes.getValue(attribute.first)));
		mArray->push_back(temp);
	}

	model.setValueType(Model::ModelValueType::ModelValueArray);
	model.setValue(mArray);

	return model;
}

Attribute ConvertUtil::model2Attributes(Model model, bool& error)
{
	Attribute attributes;
	Model::ModelArray mArray;

	model.getValue(mArray, error);
	for (auto &attr : mArray) {
		TEXT value;
		attr.getValue(value, error);
		attributes.setValue(attr.getKey(), value);
	}

	return attributes;
}

void ConvertUtil::jsonValue2Model(JsonValue value, Model& iModel, bool& error)
{
	switch(value.getValueType()) {
		case JsonValue::JsonValueType::JSONInteger :
			{
				int val;
				value.getValue(val, error);
				iModel.setValue(val);
				break;
			}
		case JsonValue::JsonValueType::JSONBoolean :
			{
				bool val;
				value.getValue(val, error);
				iModel.setValue(static_cast<int>(val));
				break;
			}
		case JsonValue::JsonValueType::JSONDouble :
			{
				double val;
				value.getValue(val, error);
				iModel.setValue(val);
				break;
			}
		case JsonValue::JsonValueType::JSONObject :
			{
				JsonObject * jObject = new JsonObject();
				value.getValue(jObject, error);
				convertJSON2Model(*(jObject), iModel, error);
				break;
			}
		default :
			{
				error = true;
				return;
			}
	}
}
