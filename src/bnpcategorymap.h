#ifndef BNPCATEGORYMAP_H
#define BNPCATEGORYMAP_H

#include <QMap>

static QMap<QString, QString> bnp_category_map{
    {"Alimentation, supermarché",               "groceries"},
    {"Musique, livres, films",                  "entertainment"},
    {"Loisirs et sorties - Autres",             "entertainment"},
    {"Divertissements, sorties culturelles",    "entertainment"},
    {"Transports en commun",                    "transport"},
    {"Taxi, vtc",                               "transport"},
    {"Restaurants, bars",                       "restaurants"},
    {"Virement émis",                           "transfers"},
    {"Banque - Autres",                         "transfers"},
    {"Achats, shopping",                        "shopping"},
    {"Pharmacie",                               "health"},
    {"Santé - Autres",                          "health"},
    {"Voyages, vacances",                       "travel"},
    {"Location de véhicule",                    "travel"},
    {"Transports et véhicules - Autres",        "travel"},
    {"Billet d'avion, Billet de train",         "travel"},
    {"Assurance véhicule",                      "insurance"},
    {"Assurance habitation",                    "insurance"},
    {"?????????",                               "services"},
    {"Téléphone",                               "utilities"},
    {"Internet, TV",                            "utilities"},
    {"Retrait d'espèce",                        "cash"},
    {"Loyer",                                   "rent"},
    {"Frais bancaires",                         "bank fees"},
    {"Sport",                                   "sport"},
    {"Scolarité, études",                       "education"},
    {"Bricolage et jardinage",                  "education"},
    {"Cadeaux",                                 "gifts"},
    {"Taxe d'habitation",                       "taxes"},
    {"Impôts et taxes - Autres",                "taxes"},
    {"Impôt sur le revenu",                     "taxes"},
    {"Salaires et revenus d'activité",          "income"},
    {"Virement reçu",                           "income"},
    {"Remboursement",                           "income"},
    {"Home",                                    "home"},
    {"Autres dépenses à catégoriser",           "uncategorized"},
    {"Virement interne",                        "internal transfer"}};

#endif // BNPCATEGORYMAP_H
