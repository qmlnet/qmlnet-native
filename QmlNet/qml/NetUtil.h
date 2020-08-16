#pragma once

#define Container(kind) struct Net ## kind ## Container {\
    QSharedPointer<kind> data;\
};
#define SideEffecter(kind, name, function) Q_DECL_EXPORT void net_ ## name ## _ ## function (Net ## kind ## Container* container) {\
    container->data->function();\
}
#define SimpleGetter(kind, name, property, ret) Q_DECL_EXPORT ret net_ ## name ## _ ## property (Net ## kind ## Container* container) {\
    return container->data->property();\
}
#define Creator(kind, name) Q_DECL_EXPORT Net ## kind ## Container* net_ ## name ## _create() {\
    return new Net ## kind ## Container{\
        .data = QSharedPointer<kind>(new kind)\
    };\
}
#define Deleter(kind, name) Q_DECL_EXPORT void net_ ## name ## _destroy (Net ## kind ## Container* container) {\
    delete container;\
}
#define WrappedGetter(kind, name, property, returnKind) Q_DECL_EXPORT Net ## returnKind ## Container* net_ ## name ## _ ## property (Net ## kind ## Container* container){\
    return new Net ## returnKind ## Container {\
        .data = QSharedPointer<returnKind>(new returnKind(container->data->property()))\
    };\
}
#define QStringGetter(kind, name, property) Q_DECL_EXPORT const char* net_ ## name ## _ ## property (Net ## kind ## Container* container) {\
    return container->data->property().toUtf8().constData();\
};
#define Publicizer(superclass, function) void function() {\
    superclass::function();\
}

#define UnwrapVal(in) *(in->data.data())
#define UnwrapObj(in) in->data.data()