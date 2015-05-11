CPPFLAG= -O2 -std=c++11 -Wall
FNAME=a3a.txt
PNAME=a3a.t
EPSILON=0.05
T=50
RM=rm -rf

tree: tree.cpp  exampleClass.h locationOfMinCon.h func.cpp func.h structure.h
	g++ $(CPPFLAG) tree.cpp func.cpp -o $@

tree_pred_func.cpp: tree $(FNAME)
	./tree $(FNAME) $(EPSILON) > $@


predict_tree: tree_predictor.cpp tree_pred_func.cpp $(PNAME)
	$(RM) tree
	g++ $(CPPFLAG) tree_predictor.cpp tree_pred_func.cpp -o tree_predictor
	$(RM) tree_pred_func.cpp
	./tree_predictor $(PNAME) > ./tree_prediction.txt

run_tree: predict_tree

forest: forest.cpp exampleClass.h locationOfMinCon.h forest_func.cpp forest_func.h structure.h
	g++ $(CPPFLAG) forest.cpp forest_func.cpp -o $@

forest_pred_func.cpp: forest $(FNAME)
	./forest $(FNAME) $(T) > $@

predict_forest: forest_predictor.cpp forest_pred_func.cpp $(PNAME)
	$(RM) forest
	g++ $(CPPFLAG) forest_predictor.cpp forest_pred_func.cpp -o forest_predictor
	$(RM) forest_pred_func.cpp
	./forest_predictor $(PNAME) > ./forest_prediction.txt

run_forest: predict_forest

clean:
	$(RM) tree_predictor tree_prediction.txt forest_predictor forest_prediction.txt
