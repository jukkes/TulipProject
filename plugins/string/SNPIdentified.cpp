/**
 *
 * This file is part of Tulip (www.tulip-software.org)
 *
 * Authors: David Auber and the Tulip development Team
 * from LaBRI, University of Bordeaux
 *
 * Tulip is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Tulip is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 */

#include <tulip/TulipPluginHeaders.h>
#include <tulip/TulipViewSettings.h>

using namespace tlp;

namespace {
const char * paramHelp[] = {
    //level
    HTML_HELP_OPEN() \
    HTML_HELP_DEF( "type", "String Collection" ) \
      HTML_HELP_DEF( "default", "ALL" )   \
    HTML_HELP_BODY() \
    "Allow to display only a specific level" \
    HTML_HELP_CLOSE(),

    //options
    HTML_HELP_OPEN() \
    HTML_HELP_DEF( "type", "String Collection" ) \
      HTML_HELP_DEF( "default", "ALL" )   \
    HTML_HELP_BODY() \
    "Allow to choose the option to display" \
    HTML_HELP_CLOSE(),

    //approximation
    HTML_HELP_OPEN() \
    HTML_HELP_DEF( "type", "String Collection" ) \
      HTML_HELP_DEF( "default", "1" )   \
    HTML_HELP_BODY() \
    "Allow to render an approximation of the positions" \
    HTML_HELP_CLOSE()
};
}

//allow to display only a specific variable level
#define LEVEL_DISPLAY "ALL;SNP;VL1;VL2;VL3;VL4;VL5;VL6"
#define INFORMATIONS "ALL;POSITIONS;DISEASES"
#define APPROXIMATIONS "1;10^3;10^6"
class SNPIdentified: public tlp::StringAlgorithm {
public:
  PLUGININFORMATION("SNP identified","Jules Teulade-Denantes","2012/03/16","Identify SNPs related to a disease","1.0","")
  SNPIdentified(const tlp::PluginContext* context): StringAlgorithm(context) {  
    addInParameter<StringCollection>("levelSelection", paramHelp[0], LEVEL_DISPLAY);
    addInParameter<StringCollection>("displayOption", paramHelp[1], INFORMATIONS);
    addInParameter<StringCollection>("positionApproximation", paramHelp[2], APPROXIMATIONS);
  }

  bool run() {
    StringCollection levelSelection(LEVEL_DISPLAY);
    StringCollection displayOption(INFORMATIONS);
    StringCollection positionApproximation(APPROXIMATIONS);
    levelSelection.setCurrent(0);

    if (dataSet != NULL) {
      dataSet->get("levelSelection",levelSelection);
      dataSet->get("displayOption",displayOption);
      dataSet->get("positionApproximation",positionApproximation);
    }
    IntegerProperty *level = graph->getProperty<IntegerProperty>("level");
    IntegerProperty *position = graph->getProperty<IntegerProperty>("position");

    // Sets different shapes and colors for each layer of the tree
    IntegerProperty *viewShape = graph->getProperty<IntegerProperty>("viewShape");
    ColorProperty *viewColor = graph->getProperty<ColorProperty>("viewColor");

    pluginProgress->setComment("Copying nodes values");
    node n;

    forEach(n, graph->getNodes()) {
        //all the levels or a specific level
        if (levelSelection.getCurrentString() == "ALL" || levelSelection.getCurrent() - 1 == level->getNodeValue(n)) {
            //truncatedPosition truncates the label node related to the position approximation chosen
            std::string truncatedPosition = position->getNodeStringValue(n).substr(0,position->getNodeStringValue(n).size() - positionApproximation.getCurrent() * 3);
            std::string nodeLabel = "";
            //if we choose to display diseases  && condition on a node (pvalue for example)
            if (displayOption.getCurrent()%2 == 0 && position->getNodeValue(n)%20 == 0) {
                //we choose a specific layout for the identified SNPS
                viewShape->setNodeValue(n, tlp::NodeShape::Star);
                viewColor->setNodeValue(n, Color::Brown);
                //we print † for the disease and the node position
                nodeLabel = "\n\n†\n " + truncatedPosition + " ";
            } else if (displayOption.getCurrent() < 2) { //if we choose to display all the nodes positions
                nodeLabel = "\n\n " + truncatedPosition + " ";
            } //otherwise, we don't display anything
            result->setNodeValue(n,nodeLabel);
        }
    }

    return true;
  }
};

PLUGIN(SNPIdentified)