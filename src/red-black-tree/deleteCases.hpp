//
// Created by Abdelouahad Ait hamd on 1/8/23.
//
#pragma once
namespace  ft{
/*
     * @Description
     *  @OPTION : CASE_O
     *             exit
     *  @OPTION : CASE_1
     *              double black node is the root
     *                  do nothing and go to  @CASE_0
     *  @OPTION : CASE_2
     *            sibling is Red and and sibling's children are black
     *             Do the following:
     *             - rotate the sibling node and go check other cases
     *  @OPTION: CASE_3
     *            parent , sibling and sibling children are all black
     *            Do the following :
     *                 - then make sibling Red
     *                  this reduces black node for both the paths from parent
     *                   now parent is new double black node
     *                   which  needs further processing by back to @CASE_1
     *  @OPTION: CASE_4
     *            sibling color is black, parent is red and sibling children are all black
     *            do the following :
     *             - swap colors between sibling and parent and go back to @CASE_0
     *             this increases one black node on double black node path but does not effect
     *             black node count on the sibling path
     *  @OPTION: CASE_5
     *            if sibling is black, double black node is left of its parent,
     *            sibling's right child is black and sibling's left child is red
     *            do the following:
     *            - right rotate siblings left child and swap colors
     *               and then go to @CASE_6
     *  @OPTION: CASE_6
     *            if sibling is black , double black node is left child of its parent
     *              siblings left child is black and sibling's right child is red
     *              do the following :
     *                  - set the sibling color to the parent color
     *                  - make parent black
     *                  - make sibling's right child black
     *                  - lefft rotate at sibling without any change of color
     *                this removes double black node
     *                  go back to CASE_0
     *
     *   @REMINDER:
     *           @CASE_1 , @CASE_2, @CASE_6, the root of RBT need to be update if we find that the
     *            node working on parent is leaf
     */
enum deleteCases{
    /*
     * @OPTION : CASE_O
     *             the deletion is
     */
    CASE_0,
    /*
     *  @OPTION : CASE_1
     *              double black node is the root
     *                  do nothing and go to  @CASE_0
     */
    CASE_1,
    /*
     *  @OPTION : CASE_2
     *            sibling is Red and and sibling's children are black
     *             Do the following:
     *             - rotate the sibling node and go check other cases
    */
    CASE_2,
    /*
     * @OPTION: CASE_3
     *            parent , sibling and sibling children are all black
     *            Do the following :
     *                 - then make sibling Red
     *                  this reduces black node for both the paths from parent
     *                   now parent is new double black node
     *                   which  needs further processing by back to @CASE_1
     */
    CASE_3,
    /*
     *    @OPTION: CASE_4
     *            sibling color is black, parent is red and sibling children are all black
     *            do the following :
     *             - swap colors between sibling and parent and go back to @CASE_0
     *             this increases one black node on double black node path but does not effect
     *             black node count on the sibling path
     */
    CASE_4,
    /*
     * @OPTION: CASE_5
     *            if sibling is black, double black node is left of its parent,
     *            sibling's right child is black and sibling's left child is red
     *            do the following:
     *            - right rotate siblings left child and swap colors
     *               and then go to @CASE_6
     */
    CASE_5,
    /*
     * @OPTION: CASE_6
     *            if sibling is black , double black node is left child of its parent
     *              siblings left child is black and sibling's right child is red
     *              do the following :
     *                  - set the sibling color to the parent color
     *                  - make parent black
     *                  - make sibling's right child black
     *                  - lefft rotate at sibling without any change of color
     *                this removes double black node
     *                  go back to CASE_0
     */
    CASE_6
};
}
