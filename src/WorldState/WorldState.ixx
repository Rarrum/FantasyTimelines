module;

export module WorldState;

export import :Timeline;
export import :World;
export import :Character;

// The initial state of the world and timelines that apply after it.
export struct Universe final
{
    World InitialWorld;
    Timeline AllChanges;
};
