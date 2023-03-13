#ifndef SWAYFIRE_SIGNALS_HPP
#define SWAYFIRE_SIGNALS_HPP

#include <wayfire/geometry.hpp>
#include <wayfire/nonstd/observer_ptr.h>
#include <wayfire/object.hpp>

class INode;
class SplitNode;
class ViewNode;
class Workspace;

using Node = nonstd::observer_ptr<INode>;
using SplitNodeRef = nonstd::observer_ptr<SplitNode>;
using ViewNodeRef = nonstd::observer_ptr<ViewNode>;
using WorkspaceRef = nonstd::observer_ptr<Workspace>;

// ========================================================================== //
// == Swayfire Lifecycle ==

/// NAME: swf-init
/// ON: output
/// WHEN: After swayfire is initialized.
struct SwayfireInit {};

/// NAME: swf-fini
/// ON: output
/// WHEN: Before swayfire is finalized.
struct SwayfireFinish {};

// ========================================================================== //
// == Output Signals ==

/// NAME: swf-active-node-changed
/// ON: output
/// WHEN: When a workspace on the output's active node changes.
struct ActiveNodeChangedSignalData {
    Node old_node, new_node;
};

/// NAME: swf-root-node-changed
/// ON: output
/// WHEN: When one of a workspace on the output's root nodes changes.
struct RootNodeChangedSignalData {
    WorkspaceRef workspace;
    bool floating;

    // Both of these are non-null in the event of a swap action.
    Node old_root, new_root;
};

// ========================================================================== //
// == Node Lifecycle ==

/// NAME: swf-view-node-attached
/// ON: output
/// WHEN: After the view node is initialized.

/// NAME: detached
/// ON: ViewNode, output(swf-view-node-)
/// WHEN: When the view node is destroyed.

/// NAME: swf-split-node-attached
/// ON: output
/// WHEN: After the split node is initialized.

// ========================================================================== //
// == Node Signals ==

/// NAME: geometry-changed
/// ON: INode
/// WHEN: When the node's geometry is set.

struct GeometryChangedSignalData {
    wf::geometry_t old_geo, new_geo;
};

/// NAME: title-changed
/// ON: INode
/// WHEN: When the node's title is updated.
struct TitleChangedSignal {};

/// NAME: padding-changed
/// ON: INode
/// WHEN: When the node's padding changes.
struct PaddingChangedSignal {};

// ========================================================================== //
// == View Node Signals ==

/// NAME: prefered-split-type-changed
/// ON: ViewNode
/// WHEN: When the view node's prefered_split_type changes.

// ========================================================================== //
// == Split Node Signals ==

/// NAME: child-inserted
/// ON: SplitNode
/// WHEN: When a new child is inserted into the node.
struct ChildInsertedSignal {
    /// The node that triggered the signal
    Node node;
};

/// NAME: child-removed
/// ON: SplitNode
/// WHEN: When a child is removed from the node.
struct ChildRemovedSignal {
    /// The node that triggered the signal
    Node node;
};

/// NAME: child-swapped
/// ON: SplitNode
/// WHEN: When a child of the node is swapped for another node.

struct ChildSwappedSignalData {
    Node old_node; ///< The swapped-out node.
    Node new_node; ///< The swapped-in node.
};

/// NAME: children-swapped
/// ON: SplitNode
/// WHEN: When two of the node's children are swapped.
struct ChildrenSwappedSignal {
};

/// NAME: split-type-changed
/// ON: SplitNode
/// WHEN: When the split type of the node changes.
struct SplitTypeChangedSignal {};

/// Data passed on view-node signals emitted from swayfire
struct ViewNodeSignalData {
    /// The node that triggered the signal
    ViewNodeRef node;
};

/// Data passed on split-node signals emitted from swayfire
struct SplitNodeSignalData {
    /// The node that triggered the signal
    SplitNodeRef node;
};

/// Data passed on node signals emitted from swayfire
struct NodeSignalData {
    /// The node that triggered the signal
    Node node;
};

#endif // ifndef SWAYFIRE_SIGNALS_HPP
