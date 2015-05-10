CPPFLAG= -O2 -std=c++11 -Wall
FNAME=a1a.train
PNAME=a1a.test
EPSILON=0.05
RM=rm -rf

tree: tree.cpp exampleClass.cpp exampleClass.h locationOfMinCon.h func.cpp func.h structure.h
	g++ $(CPPFLAG) tree.cpp exampleClass.cpp func.cpp -o $@

tree_pred_func.cpp: tree $(FNAME)
	./tree $(FNAME) $(EPSILON)


predict_tree: tree_predictor.cpp tree_pred_func.cpp $(PNAME)
	$(RM) tree
	g++ tree_predictor.cpp tree_pred_func.cpp -o tree_predictor
	$(RM) tree_pred_func.cpp
	./tree_predictor $(FNAME) > ./tree_prediction.txt

run_tree: predict_tree

clean:
	$(RM) tree_predictor tree_prediction.txt
